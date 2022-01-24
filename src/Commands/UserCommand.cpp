//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "UserCommand.hpp"

UserCommand::UserCommand() {}

UserCommand::UserCommand(const UserCommand &other) : Command((Command&)other) {}

UserCommand &UserCommand::operator=(const UserCommand &other) {
    if (&other == this)
        return *this;
    Command::operator=((Command&)other);
    return *this;
}

UserCommand::UserCommand(const MessageBNF &messageBnf, int sock_source) : Command(messageBnf, sock_source) { }

UserCommand::~UserCommand() { }

std::vector<MessageBNF> UserCommand::exec() {
    std::vector<MessageBNF> result;
    ApplicationData::Ptr app_data = ApplicationData::instance();

    app_data->users[m_sockSource]->setUserName(m_message.arguments[0]);
    app_data->users[m_sockSource]->setRealName(m_message.arguments[3].substr(1, m_message.arguments[3].size() - 1));

    return result;
}
