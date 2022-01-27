#include <src/ApplicationData.hpp>
#include "OperCommand.hpp"

OperCommand::OperCommand() { }

OperCommand::OperCommand(const OperCommand &other) { }

OperCommand &OperCommand::operator=(const OperCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

OperCommand::OperCommand(const Message &message) : ClientMessage(message) { }

OperCommand::~OperCommand() { }

ft::optional<ServerResponse> OperCommand::exec() {
    ServerResponse response;
    ApplicationData::Ptr app_data = ApplicationData::instance();

    std::string passedUser = m_message.messageBnf.arguments[0];
    std::string passedPassword = m_message.messageBnf.arguments[1];

    if (passedUser != "admin" || passedPassword != app_data->operatorPass) {
        Message msg ("464 " + m_message.m_from->getNick() + " :Password incorrect", m_message.m_from);
        response.m_replies.push_back(msg);
        return response;
    }

    response.m_replies.push_back(Message("381 " + m_message.m_from->getNick() + " :You are now an IRC operator", m_message.m_from));
    response.m_replies.push_back(Message("MODE " + m_message.m_from->getNick() + " +o", m_message.m_from));
    m_message.m_from->setIsOperator(true);

    return response;
}
