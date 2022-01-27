#include "SocketServer.hpp"
#include "src/ApplicationData.hpp"
#include <stdexcept>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <fcntl.h>
#include <poll.h>
#include <arpa/inet.h>
#include <utils.hpp>

SocketServer::SocketServer(unsigned short port, int max_clients) :
        m_port(port),
        m_max_clients(max_clients),
        m_running(true)
{
    bzero(m_in_buffer, BUFFER_SIZE);

    m_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    int option = 1;
    setsockopt(m_sock_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if (m_sock_fd <= 0)
        throw std::runtime_error("Failed to initialize socket");

    if (fcntl(m_sock_fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Failed to initialize socket non-block");

    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    m_addr.sin_port = htons(port);

    int bind_result = bind(m_sock_fd, (sockaddr*)&m_addr, sizeof(m_addr));
    if (bind_result < 0)
        throw std::runtime_error("Failed to bind socket: " + std::string(strerror(errno)));
    pollfd pfd = {m_sock_fd, POLLRDNORM, 0};
    m_pollfds.push_back(pfd);
}

void SocketServer::Listen() {
    int listen_result = listen(m_sock_fd, m_max_clients);
    if (listen_result < 0)
        throw std::runtime_error("Failed to listen socket: "  + std::string(strerror(errno)));
}

int SocketServer::Accept() {
    socklen_t len = sizeof(m_addr);
    int conn_fd = accept(m_sock_fd, (sockaddr*)&m_addr, &len);
    if (conn_fd < 0)
        throw std::runtime_error("Accept error: "  + std::string(strerror(errno)));
    return conn_fd;
}

void SocketServer::handleNewTcpConnection() {
    if (m_pollfds[0].revents & POLLRDNORM) {
        int new_connfd = Accept();
        pollfd pfd = {new_connfd, POLLRDNORM, 0};

        ApplicationData::instance()->users[new_connfd] = User::Ptr(new User(new_connfd));

        m_pollfds.push_back(pfd);
    }
}

/**
 * Вычитывает данные из сокета sockfd.
 * Если флаг auto_close задан как true - то при возможности закрыть соединение оно закрывается автоматически
 * @param sockfd
 * @param auto_close
 * @return Результат чтения (см. ReadResult)
 */
ReadResult SocketServer::readFromClient(int sockfd, bool auto_close) {
    bzero(m_in_buffer, BUFFER_SIZE);
    int n = read(sockfd, m_in_buffer, BUFFER_SIZE);
    if (n == 0) {
        if (auto_close)
            close(sockfd);
        return RR_Closed;
    }

    if (n == -1)
    {
        if (errno == ECONNRESET) { /* Соединение переустановлено клиентом */
            if (auto_close)
                close(sockfd);
            return RR_ConnReset;
        }
        return RR_Error;
    }
    return RR_Ok;
}

/**
 * Handle all established TCP connections.
 *
 * @param connections - how many connections poll functions return.
 */
void SocketServer::handleExistingTcpConnection(int connections) {
    ApplicationData::Ptr appdata = ApplicationData::instance();
    for (pollIt it = m_pollfds.begin() + 1; it != m_pollfds.end(); ) {
        if (it->revents & POLLRDNORM) {
            /* Read data from client */
            if (readFromClient(it->fd) != RR_Ok) {
                std::cout << "Client " << appdata->users[it->fd]->generateFullUsername() << " disconnected" << std::endl;
                userDisconnected(it);
                continue;
            }
            handleIncomingData(it->fd);
        }
        it++;
    }
}

void SocketServer::Loop() {
    ApplicationData::Ptr appdata = ApplicationData::instance();
    while (m_running) {
        int ready = poll(m_pollfds.data(), m_pollfds.size(), INFTIM);
        if (ready == -1)
            throw std::runtime_error("Poll error: "  + std::string(strerror(errno)));
        handleNewTcpConnection();
        handleExistingTcpConnection(ready - 1);
        appdata->commandsQueue.handleCommands();
         disconnectUsersInQueue();
    }
    CloseAllConnection();
}

void SocketServer::handleIncomingData(int conn_fd) {
    std::string str_buffer(m_in_buffer);

    ApplicationData::Ptr appdata = ApplicationData::instance();

    std::string delimiter = (str_buffer[str_buffer.size() - 2] == '\x0d') ? "\x0d\x0a" : "\x0a";

    std::vector<std::string> raw_commands = ft::split(m_in_buffer, delimiter);

    for (int i = 0; i < raw_commands.size(); ++i) {
        Message msg(raw_commands[i], User::Ptr(0), appdata->users[conn_fd]);
        ClientMessage::Ptr new_cmd = appdata->factory.createCommand(msg);
        if (new_cmd)
            appdata->commandQueue.push_back(new_cmd);
    }
}

void SocketServer::stop() {
    m_running = false;
}

void SocketServer::CloseAllConnection() {
    for (int i = 1; i < m_pollfds.size(); ++i) {
//        shutdown(m_pollfds[i].fd, 0);
        close(m_pollfds[i].fd);
    }
//    shutdown(m_pollfds[0].fd, 0);
    close(m_pollfds[0].fd);
}

void SocketServer::Write(const ServerResponse & response) {
    for (int i = 0; i < response.m_replies.size(); ++i) {
        Write(response.m_replies[i]);
    }
}

void SocketServer::Write(const Message &message) {
    std::string str = (std::string)message.messageBnf;

    ApplicationData::Ptr app_data = ApplicationData::instance();
    if (message.m_from)
        str = ":" + message.m_from->generateFullUsername() + " " + str;
    else
        str = ":" + app_data->serverName + " " + str;

    write(message.m_to->getSockFd(), str.data(), str.size());
}

void SocketServer::disconnectUser(User::Ptr user) {
    for (pollIt it = m_pollfds.begin(); it != m_pollfds.end(); it++) {
        if (it->fd == user->getSockFd()) {
            int fd = it->fd;
            userDisconnected(it);
            close(fd);
            return;
        }
    }
}

/**
 * Function called if user disconnected in RST-style - without send QUIT or DISCONNECT messages
 * Here we should remove users from all channels and notify other users, that left user not available anymore.
 * @param iterator
 */
void SocketServer::userDisconnected(SocketServer::pollIt & iterator) {
    ApplicationData::Ptr appdata = ApplicationData::instance();

    User::Ptr user = appdata->users[iterator->fd];
    // Clean channels
    std::vector<IRCChannel::Ptr> channels = appdata->userChannels(user);
    for (int i = 0; i < channels.size(); ++i) {
        channels[i]->removeUser(user);
    }

    appdata->users.erase(iterator->fd);
    appdata->lockedCap.erase(iterator->fd);

    typedef std::deque<ClientMessage::Ptr>::iterator CMIt;

    for (CMIt it = appdata->commandQueue.begin(); it != appdata->commandQueue.end() ; ) {
        if (it->get()->m_message.m_from->getSockFd() == iterator->fd)
            it = appdata->commandQueue.erase(it);
        else
            it++;
    }

    m_pollfds.erase(iterator);
}

void SocketServer::appendToDisconnectQueue(int sockfd) {
    m_disconnectQueue.push_back(sockfd);
}

void SocketServer::disconnectUsersInQueue() {
    ApplicationData::Ptr appdata = ApplicationData::instance();

    for (int i = 0; i < m_disconnectQueue.size(); ++i) {
        User::Ptr user = appdata->users[m_disconnectQueue[i]];
        disconnectUser(user);
    }
    m_disconnectQueue.clear();

}

