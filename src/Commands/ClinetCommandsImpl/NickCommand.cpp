//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "NickCommand.hpp"

NickCommand::NickCommand() {}

NickCommand::NickCommand(const NickCommand &other) : ClientMessage((ClientMessage&)other) {}

NickCommand::NickCommand(const Message &message) : ClientMessage(message) {}

NickCommand &NickCommand::operator=(const NickCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

NickCommand::~NickCommand() { }

ft::optional<ServerResponse> NickCommand::exec() {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    User::Ptr user = app_data->users[m_message.m_from->getSockFd()];

    user->setNick(m_message.messageBnf.arguments[0]);

    return ft::optional<ServerResponse>();
}