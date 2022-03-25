#include <iostream>
#include <cstdlib>
#include "src/Server/SocketServer.hpp"
#include "ApplicationData.hpp"
int main(int argc, char *argv[]) {

    {
        if (argc != 3)
        {
            std::cerr << "Wrong argument count. Usage: ./ircserv <port> <pass>." << std::endl;
            exit(1);
        }

        std::string password(argv[2]);
        if (password.empty()) {
            std::cerr << "Password must not be empty." << std::endl;
            exit(1);
        }

        int port = std::atoi(argv[1]);
        if (port < 1 || port > 65535) {
            std::cerr << "Invalid port. Must be in range [1, 65535]." << std::endl;
            exit(1);
        }

        SocketServer ss(port, 100);

        ApplicationData::instance()->server = &ss;
        ApplicationData::instance()->serverName = "ft_irc.42";
        ApplicationData::instance()->operatorPass = "123456";
        ApplicationData::instance()->password = password;

        ss.Listen();
        ss.Loop();
    }

    return 0;
}
