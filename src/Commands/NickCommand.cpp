//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "NickCommand.hpp"

NickCommand::NickCommand() {}

NickCommand::NickCommand(const NickCommand &other) : Command((Command&)other) {}

NickCommand &NickCommand::operator=(const NickCommand &other) {
    if (&other == this)
        return *this;
    Command::operator=((Command&)other);
    return *this;
}

NickCommand::NickCommand(const MessageBNF &messageBnf, int sock_source) : Command(messageBnf, sock_source) {
    
}

NickCommand::~NickCommand() { }

std::vector<MessageBNF> NickCommand::exec() {
    std::vector<MessageBNF> result;

    ApplicationData::Ptr app_data = ApplicationData::instance();
    app_data->users[m_sockSource]->setUserName(m_message.arguments[0]);

    return result;
}
