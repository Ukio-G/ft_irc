//
// Created by ukio on 1/24/22.
//

#include <utils.hpp>
#include "ApplicationData.hpp"


/* Private (Not allowed in singleton) */

ApplicationData::ApplicationData() { }

ApplicationData::ApplicationData(const ApplicationData &other) { }

ApplicationData &ApplicationData::operator=(const ApplicationData &other) { return *this; }

ApplicationData::~ApplicationData() { }

ApplicationData::Ptr ApplicationData::instance() {
    static Ptr result (new ApplicationData);
    return result;
}

ft::optional<User::Ptr> ApplicationData::getUserByNick(const std::string & nick) {
    ft::optional<User::Ptr> result;

    typedef std::map<int, User::Ptr>::iterator uIt;
    ApplicationData::Ptr data = ApplicationData::instance();

    std::map<int, User::Ptr> & users = data->users;

    for (uIt it = users.begin();it != users.end(); it++) {
        if (it->second->getNick() == nick)
            return it->second;
    }
    return ft::nullopt;
}

std::vector<IRCChannel::Ptr> ApplicationData::userChannels(User::Ptr user) {
    std::vector<IRCChannel::Ptr> result;
    ApplicationData::Ptr app_data = ApplicationData::instance();
    typedef std::map<std::string, IRCChannel::Ptr>::iterator chIt;

    for (chIt it = app_data->channels.begin(); it != app_data->channels.end() ; it++) {
        if (it->second->isUserAvailable(user))
            result.push_back(it->second);
    }

    return result;
}



