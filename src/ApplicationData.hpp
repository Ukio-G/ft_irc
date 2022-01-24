#ifndef APPLICATIONDATA_HPP
#define APPLICATIONDATA_HPP

#include <vector>
#include <map>
#include <src/Commands/Command.hpp>
#include <deque>
#include <src/Commands/CommandFactory.hpp>
#include <src/Commands/CommandsHandler.hpp>
#include "utils/shared_ptr.hpp"
#include "User.hpp"
#include "SocketServer.hpp"

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
    std::deque<Command::Ptr> commandQueue;
    CommandFactory factory;
    CommandsHandler commandsHandler;
    SocketServer * server;
    std::string password;
    std::string serverName;
};

#endif
