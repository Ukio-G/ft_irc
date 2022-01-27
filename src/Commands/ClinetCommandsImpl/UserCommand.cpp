#include <src/ApplicationData.hpp>
#include <optional.hpp>
#include "UserCommand.hpp"

UserCommand::UserCommand() {}

UserCommand::UserCommand(const UserCommand &other) : ClientMessage((ClientMessage&)other) {}

UserCommand::UserCommand(const Message &message) : ClientMessage(message) {}

UserCommand &UserCommand::operator=(const UserCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

UserCommand::~UserCommand() { }

ft::optional<ServerResponse> UserCommand::exec() {
    ServerResponse result;

    ApplicationData::Ptr app_data = ApplicationData::instance();
    MessageBNF & msg = m_message.messageBnf;

    const std::string & user_name = msg.arguments[0];
    const std::string & real_name = msg.arguments[3].substr(1, msg.arguments[3].size() - 1);

    User::Ptr user = app_data->users[m_message.m_from->getSockFd()];

    user->setUserName(user_name);
    user->setRealName(real_name);

    const std::string & nick = user->getNick();

    Message welcome(MessageBNF("001 " + nick + " :Welcome to IRC Server " + user->generateFullUsername()), user);

    result.m_replies.push_back(welcome);

    /* Send 25x messages after registration on server */
    ServerStatus & status = app_data->serverStatus;
    result.m_replies.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERCLIENT, user));
    result.m_replies.push_back(status.getReplyMessage(ServerStatus::RPL_LUSEROP, user));
    result.m_replies.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERUNKNOWN, user));
    result.m_replies.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERCHANNELS, user));
    result.m_replies.push_back(status.getReplyMessage(ServerStatus::RPL_LUSERME, user));
    result.m_replies.push_back(Message("422 " + user_name + " :MOTD File is missing", user));

    return result;
}
