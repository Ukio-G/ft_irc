#include <src/ApplicationData.hpp>
#include "PassCommand.hpp"

PassCommand::PassCommand() {}

PassCommand::PassCommand(const PassCommand &other) : ClientMessage((ClientMessage&)other) {
}

PassCommand &PassCommand::operator=(const PassCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

PassCommand::~PassCommand() { }

PassCommand::PassCommand(const Message &message) : ClientMessage(message) {}

ft::optional<ServerResponse> PassCommand::exec() {
    ServerResponse result;

    ApplicationData::Ptr app_data = ApplicationData::instance();
    User::Ptr user = m_message.m_from;

    if (app_data->password == m_message.messageBnf.arguments[0]) {
        user->setAuthorized(true);
        result.m_replies.push_back(Message("PASS Correct password", user));
    } else {
        result.m_replies.push_back(Message("464 * :Password incorrect", user));
        result.m_replies.push_back(Message("ERROR :Password incorrect", user));
    }

    return result;
}

