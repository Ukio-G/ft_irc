#include "SocketServer.hpp"
#include "ApplicationData.hpp"
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
    port(port),
    max_clients(max_clients)
{
    bzero(buffer, BUFFER_SIZE);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd <= 0)
        throw std::runtime_error("Failed to initialize socket");

    if (fcntl(sock_fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Failed to initialize socket non-block");

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);

    int bind_result = bind(sock_fd, (sockaddr*)&addr, sizeof(addr));
    if (bind_result < 0)
        throw std::runtime_error("Failed to bind socket: " + std::string(strerror(errno)));
    pollfd pfd = {sock_fd, POLLRDNORM, 0};
    pollfds.push_back(pfd);
}

void SocketServer::Listen() {
    int listen_result = listen(sock_fd, max_clients);
    if (listen_result < 0)
        throw std::runtime_error("Failed to listen socket: "  + std::string(strerror(errno)));
}

int SocketServer::Accept() {
    socklen_t len = sizeof(addr);
    int conn_fd = accept(sock_fd, (sockaddr*)&addr, &len);
    if (conn_fd < 0)
        throw std::runtime_error("Accept error: "  + std::string(strerror(errno)));
    return conn_fd;
}

void SocketServer::handleNewTcpConnection() {
    if (pollfds[0].revents & POLLRDNORM) {
        int new_connfd = Accept();
        pollfd pfd = {new_connfd, POLLRDNORM, 0};

        ApplicationData::instance()->users[new_connfd] = User::Ptr(new User(new_connfd));

        pollfds.push_back(pfd);
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
    bzero(buffer, BUFFER_SIZE);
    int n = read(sockfd, buffer, BUFFER_SIZE);
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
    for (pollIt it = pollfds.begin() + 1; it != pollfds.end(); ) {
        if (it->revents & POLLRDNORM) {
            /* Read data from client */
            if (readFromClient(it->fd) != RR_Ok) {
                std::cout << "Client " << appdata->users[it->fd]->generateFullUsername() << " disconnected" << std::endl;
                it = pollfds.erase(it);
                continue;
            }
            handleIncomingData(it->fd);
        }
        it++;
    }
}

void SocketServer::WriteStr(const std::string & string, int conn_fd) {
    write(conn_fd, string.data(), string.size());
}

void SocketServer::Write(char * data, size_t n, int conn_fd) {
    write(conn_fd, data, n);
}

void SocketServer::Loop() {
    while (true) {
        int ready = poll(pollfds.data(), pollfds.size(), INFTIM);
        if (ready == -1)
            throw std::runtime_error("Poll error: "  + std::string(strerror(errno)));
        handleNewTcpConnection();
        handleExistingTcpConnection(ready - 1);
    }
}

void SocketServer::handleIncomingData(int conn_fd) {
    std::string str_buffer(buffer);

    std::string delimiter = (str_buffer[str_buffer.size() - 2] == '\x0d') ? "\x0d\x0a" : "\x0a";
    std::vector<std::string> raw_commands = ft::split(buffer,  delimiter);



}

