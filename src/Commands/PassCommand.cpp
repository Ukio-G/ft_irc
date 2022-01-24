//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "PassCommand.hpp"

PassCommand::PassCommand() {}

PassCommand::PassCommand(const PassCommand &other) : Command((Command&)other) {
}

PassCommand &PassCommand::operator=(const PassCommand &other) {
    if (&other == this)
        return *this;
    Command::operator=((Command&)other);
    return *this;
}

PassCommand::~PassCommand() { }

PassCommand::PassCommand(const MessageBNF &messageBnf, int sock_source) : Command(messageBnf, sock_source) {
    if (messageBnf.arguments.size() != 1)
        throw std::runtime_error("PASS: Wrong argument count");
}

std::vector<MessageBNF> PassCommand::exec() {
    std::vector<MessageBNF> result;

    ApplicationData::Ptr app_data = ApplicationData::instance();

    if (app_data->password == m_message.arguments[0]) {
        User::Ptr user = app_data->users[m_sockSource];
        user->setAuthorized(true);
        result.push_back(MessageBNF("PASS Correct password\x0d\x0a"));
    } else {
        result.push_back(MessageBNF("464 * :Password incorrect\x0d\x0a"));
        result.push_back(MessageBNF("ERROR :Password incorrect\x0d\x0a"));
    }

    return result;
}

