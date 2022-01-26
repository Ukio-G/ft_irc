#include <src/ApplicationData.hpp>
#include "ServerStatus.hpp"
#include <cstdlib>
#include <utils.hpp>

ServerStatus::ServerStatus() {}

ServerStatus::ServerStatus(const ServerStatus &other) {}

ServerStatus &ServerStatus::operator=(const ServerStatus &other) {
    if (&other == this)
        return *this;

    return *this;
}

ServerStatus::~ServerStatus() { }

Message ServerStatus::getReplyMessage(ServerStatus::Reply reply, User::Ptr to) {
    switch (reply) {
        case RPL_LUSERCLIENT:
            return rpl_luserclient(to);
        case RPL_LUSEROP:
            return rpl_luserop(to);
        case RPL_LUSERUNKNOWN:
            return rpl_luserunknown(to);
        case RPL_LUSERCHANNELS:
            return rpl_luserchannels(to);
        case RPL_LUSERME:
            return rpl_luserme(to);
        default:
            throw std::runtime_error("Invalid reply number for ServerStatus logic");
    }
}

Message ServerStatus::rpl_luserclient(User::Ptr to) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string server_name = app_data->serverName;
    size_t users_count = ApplicationData::instance()->users.size();

    Message msg(":" + server_name + " 251 " + to->getNick() + " :There are " + ft::to_string((int)users_count) + " users and 1 services on 1 servers", to);
    return msg;
}

Message ServerStatus::rpl_luserop(User::Ptr to) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string server_name = app_data->serverName;
    int operators = 0;

    typedef std::map<int, User::Ptr>::iterator uIt;


    //TODO: Fix inf. loop
//    for (uIt it = app_data->users.begin() ; it != app_data->users.end(); ) {
//        if (it->second->isOperator())
//            operators++;
//    }

    Message msg(":" + server_name + " 252 " + to->getNick() + " " + ft::to_string(operators)+ " :operator(s) online", to);
    return msg;
}

Message ServerStatus::rpl_luserunknown(User::Ptr to) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string server_name = app_data->serverName;

    Message msg(":" + server_name + " 253 " + to->getNick() + " 0 :unknown connection(s)", to);
    return msg;
}

Message ServerStatus::rpl_luserchannels(User::Ptr to) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string server_name = app_data->serverName;
    size_t channels_count = ApplicationData::instance()->channels.size();

    Message msg(":" + server_name + " 254 " + to->getNick() + " "+ ft::to_string((int)channels_count)+" :channels formed", to);
    return msg;
}

Message ServerStatus::rpl_luserme(User::Ptr to) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string server_name = app_data->serverName;
    size_t users_count = ApplicationData::instance()->users.size();

    Message msg(":" + server_name + " 255 " + to->getNick() + " :I have " + ft::to_string((int)users_count) + " clients and 1 servers", to);
    return msg;
}
