//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "CapCommand.hpp"

CapCommand::CapCommand() {}

CapCommand::CapCommand(const CapCommand &other) : Command((Command&)other) {}

CapCommand &CapCommand::operator=(const CapCommand &other) {
    if (&other == this)
        return *this;
    Command::operator=((Command&)other);
    return *this;
}

CapCommand::~CapCommand() { }

CapCommand::CapCommand(const MessageBNF &messageBnf, int sock_source) : Command(messageBnf, sock_source) { }

std::vector<MessageBNF> CapCommand::exec() {
    std::vector<MessageBNF> result;
    ApplicationData::Ptr appdata = ApplicationData::instance();

    if (m_message.arguments[0] == "LS")
        result.push_back(MessageBNF("CAP * LS:\x0d\x0a"));

    if (m_message.arguments[0] == "END")
        appdata->commandsHandler.capUnlock();

    return result;
}

