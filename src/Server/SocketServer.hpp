#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP
#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <sys/poll.h>
#include <string>
#include <map>
#include <optional.hpp>
#include "ServerResponse.hpp"

#ifndef INFTIM
    #define INFTIM -1
#endif

#define BUFFER_SIZE 2048

enum ReadResult {
    RR_Ok, RR_Error, RR_ConnReset, RR_Closed
};

class SocketServer {
public:
    typedef std::vector<pollfd>::iterator pollIt;
    SocketServer(unsigned short port = 6667, int max_clients = 1000);

    /* Communication logic */
    ReadResult  readFromClient(int sockfd, bool auto_close = true);
    void        CloseAllConnection();
    int         Accept();
    void        Listen();
    void        Loop();
    void        Write(const ServerResponse & response);
    void        Write(const Message & message);


    /* Application logic */
    void handleNewTcpConnection();
    void handleExistingTcpConnection(int connections);
    void stop();
    void handleIncomingData(int conn_fd);
    void appendToDisconnectQueue(int sockfd);


private:
    unsigned short                              m_port;
    bool                                        m_running;
    int                                         m_max_clients;
    int                                         m_sock_fd;
    char                                        m_in_buffer[BUFFER_SIZE];
    sockaddr_in                                 m_addr;
    std::vector<pollfd>                         m_pollfds;
    std::vector<int>                            m_disconnectQueue; // Queue users to safe disconnect (this vector contains sockFDs)
    std::map<int, ft::optional<std::string> >   unfinished_commands;

    void userDisconnected(pollIt &iterator);
    void disconnectUser(User::Ptr user);
    void disconnectUsersInQueue();
};


#endif
