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

std::vector<Message> NickCommand::successAuth() {
    ApplicationData::Ptr app_data = ApplicationData::instance();

    std::vector<Message> result;

    User::Ptr user = app_data->users[m_message.m_from->getSockFd()];
    const std::string & nick = user->getNick();
    const std::string & user_name = user->getUserName();

    result.push_back(Message("PASS Correct password", user));
    Message welcome(MessageBNF("001 " + nick + " :Welcome to IRC Server " + user->generateFullUsername()), user);

    result.push_back(welcome);

    /* Send 25x messages after registration on server */
    ServerStatus & status = app_data->serverStatus;
    result.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERCLIENT, user));
    result.push_back(status.getReplyMessage(ServerStatus::RPL_LUSEROP, user));
    result.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERUNKNOWN, user));
    result.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERCHANNELS, user));
    result.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERME, user));
    result.push_back(Message("422 " + user_name + " :MOTD File is missing", user));

    return result;
}

bool NickCommand::isRegisterReady() {
    bool has_nick, has_user_name, password_match;
    User::Ptr user = m_message.m_from;
    password_match = user->isAuthorized();
    has_nick = !user->getNick().empty();
    has_user_name = !user->getUserName().empty();

    return has_user_name && has_nick && password_match;
}

ft::optional<ServerResponse> NickCommand::exec() {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    User::Ptr user = app_data->users[m_message.m_from->getSockFd()];
    ServerResponse result;

    if (!m_message.m_from->getNick().empty())
        return ft::nullopt;

    if (m_message.messageBnf.arguments.empty()) {
        result.m_replies.push_back(Message("461 " + m_message.m_from->getNick() + " KICK :Not enough parameters", m_message.m_from));
        return result;
    }

    std::string nick = m_message.messageBnf.arguments[0];
    if (!app_data->getUserByNick(nick).has_value())
        user->setNick(nick);
    else {
        result.m_replies.push_back(Message("433 * " + nick + " :Nickname is already in use", m_message.m_from));
        return result;
    }

    if (!isRegisterReady())
        return ft::nullopt;
    result.append(successAuth());
    return result;
}