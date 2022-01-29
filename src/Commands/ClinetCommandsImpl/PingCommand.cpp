#include "PingCommand.hpp"

PingCommand::PingCommand() {}

PingCommand::PingCommand(const PingCommand &other) : ClientMessage((ClientMessage&)other) {}

PingCommand::PingCommand(const Message &message) : ClientMessage(message) {}

PingCommand &PingCommand::operator=(const PingCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

PingCommand::~PingCommand() { }


ft::optional<ServerResponse> PingCommand::exec() {
    ServerResponse result;

    Message pong(MessageBNF("PONG " + m_message.messageBnf.arguments[0]), m_message.m_from);

    result.m_replies.push_back(pong);
    return result;
}
