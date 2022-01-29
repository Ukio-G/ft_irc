#include "UndefinedCommand.hpp"

UndefinedCommand::UndefinedCommand() { }

UndefinedCommand::UndefinedCommand(const UndefinedCommand &other) : ClientMessage((ClientMessage&)other) { }

UndefinedCommand &UndefinedCommand::operator=(const UndefinedCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

UndefinedCommand::~UndefinedCommand() { }

UndefinedCommand::UndefinedCommand(const Message &message) : ClientMessage(message) { }

ft::optional<ServerResponse> UndefinedCommand::exec() {
    ServerResponse result;
    User::Ptr from = m_message.m_from;

    std::string nick = (from->getNick().empty()) ? "*" : from->getNick();

    Message msg("421 " + nick + " " + m_message.messageBnf.command + " :Unknown command", from);
    result.m_replies.push_back(msg);

    return result;
}

