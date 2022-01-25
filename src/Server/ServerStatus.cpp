//
// Created by ukio on 1/25/22.
//

#include <src/ApplicationData.hpp>
#include "ServerStatus.hpp"
#include <cstdlib>
#include <stdlib.h>
#include <utils.hpp>

ServerStatus::ServerStatus() {}

ServerStatus::ServerStatus(const ServerStatus &other) {}

ServerStatus &ServerStatus::operator=(const ServerStatus &other) {
    if (&other == this)
        return *this;

    return *this;
}

ServerStatus::~ServerStatus() {

}

Message ServerStatus::getReplyMessage(ServerStatus::Reply reply, User::Ptr to) {
    switch (reply) {
        case RPL_LUSERCLIENT:
            return rpl_luserclient(to);
            break;
        case RPL_LUSEROP:
        {

        }
            break;
        case RPL_LUSERUNKNOWN:
        {

        }
            break;
        case RPL_LUSERCHANNELS:
        {

        }
            break;
        case RPL_LUSERME:
        {

        }
            break;
    }
}

Message ServerStatus::rpl_luserclient(User::Ptr to) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string server_name = app_data->serverName;
    size_t users_count = ApplicationData::instance()->users.size();

    Message msg(":" + server_name + " 251 " + to->getNick() + "There are " + ft::to_string((int)users_count) + " users and 1 services on 1 servers", to);
    return msg;
}

Message ServerStatus::rpl_luserop(User::Ptr to) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string server_name = app_data->serverName;
    int operators = 0;

    typedef std::map<int, User::Ptr>::iterator uIt;

    for (uIt it = app_data->users.begin() ; it != app_data->users.end(); ) {
        if (it->second->isOperator())
            operators++;
    }

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

    Message msg(":" + server_name + " 255 " + to->getNick() + "There are " + ft::to_string((int)users_count) + " users and 1 services on 1 servers", to);
    return msg;
}
