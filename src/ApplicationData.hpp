#ifndef APPLICATIONDATA_HPP
#define APPLICATIONDATA_HPP

#include <vector>
#include <map>
#include <src/Commands/ClientMessage.hpp>
#include <deque>
#include <src/Commands/CommandFactory.hpp>
#include <src/Commands/CommandsQueue.hpp>
#include <set>
#include <src/Server/ServerStatus.hpp>
#include "utils/shared_ptr.hpp"
#include "User.hpp"
#include "src/Server/SocketServer.hpp"
#include "IRCChannel.hpp"

class ApplicationData {
private:
    ApplicationData();

    ApplicationData(const ApplicationData &other);

    ApplicationData &operator=(const ApplicationData &other);
public:
    ~ApplicationData();
    typedef ft::shared_ptr<ApplicationData> Ptr;
    static ft::shared_ptr<ApplicationData> instance();

    std::string password;
    std::string operatorPass;
    std::string serverName;

    /* Internal logic's data */
    std::set<int> lockedCap; /* Clients waiting CAP END message */
    std::deque<ClientMessage::Ptr> commandQueue; // TODO: move to CommandsQueue logic with incapsulate append new commands
    std::map<std::string, IRCChannel::Ptr> channels;
    std::map<int, User::Ptr> users; /* SocketFD (client connection identifier) to User::Ptr */
    std::vector<User::Ptr> userOperator;

    /* Logics */
    SocketServer * server;
    ServerStatus serverStatus;
    CommandFactory factory;
    CommandsQueue commandsQueue;

    /* Request to find data */
    static ft::optional<User::Ptr> getUserByNick(const std::string & nick);
    static std::vector<IRCChannel::Ptr> userChannels(User::Ptr user);

};

#endif
