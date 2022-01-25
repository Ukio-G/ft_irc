#ifndef APPLICATIONDATA_HPP
#define APPLICATIONDATA_HPP

#include <vector>
#include <map>
#include <src/Commands/ClientMessage.hpp>
#include <deque>
#include <src/Commands/CommandFactory.hpp>
#include <src/Commands/CommandsHandler.hpp>
#include <set>
#include "utils/shared_ptr.hpp"
#include "User.hpp"
#include "src/Server/SocketServer.hpp"
#include "Channel.hpp"

class ApplicationData {
private:
    ApplicationData();

    ApplicationData(const ApplicationData &other);

    ApplicationData &operator=(const ApplicationData &other);
public:
    ~ApplicationData();
    typedef ft::shared_ptr<ApplicationData> Ptr;
    static ft::shared_ptr<ApplicationData> instance();

    std::map<int, User::Ptr> users;
    std::set<int> lockedCap; // Для данных sockFD заблокировано

    std::deque<ClientMessage::Ptr> commandQueue;
    std::vector<Channel> channels;
    CommandFactory factory;
    CommandsHandler commandsHandler;
    SocketServer * server;
    std::string password;
    std::string serverName;
};

#endif
