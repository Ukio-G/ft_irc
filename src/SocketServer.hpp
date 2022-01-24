#ifndef SOCKETSERVER_HPP
#define SOCKETSERVER_HPP
#include <sys/socket.h>
#include <vector>
#include <netinet/in.h>
#include <sys/poll.h>
#include <string>

#ifndef INFTIM
    #define INFTIM -1
#endif

#define BUFFER_SIZE 1024

enum ReadResult {
    RR_Ok, RR_Error, RR_ConnReset, RR_Closed
};

class SocketServer {
public:
    typedef std::vector<pollfd>::iterator pollIt;
    SocketServer(unsigned short port = 1234, int max_clients = 10);

    unsigned short port;
    int max_clients;
    int sock_fd;
    char buffer[BUFFER_SIZE];
    sockaddr_in addr;
    std::vector<pollfd> pollfds;

    void Listen();
    int Accept();
    void Loop();

    void handleNewTcpConnection();
    void handleExistingTcpConnection(int connections);
    ReadResult readFromClient(int sockfd, bool auto_close = true);
    void handleIncomingData();

    void WriteStr(const std::__cxx11::basic_string<char> &string, int conn_fd);

    void Write(char *data, size_t n, int conn_fd);

    void handleIncomingData(int conn_fd);
};


#endif
