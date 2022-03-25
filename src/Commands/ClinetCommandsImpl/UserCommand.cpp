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

std::vector<Message> UserCommand::successAuth() {
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

bool UserCommand::isRegisterReady() {
    bool has_nick, has_user_name, password_match;
    User::Ptr user = m_message.m_from;
    password_match = user->isAuthorized();
    has_nick = !user->getNick().empty();
    has_user_name = !user->getUserName().empty();

    return has_user_name && has_nick && password_match;
}


ft::optional<ServerResponse> UserCommand::exec() {
    ServerResponse result;

    ApplicationData::Ptr app_data = ApplicationData::instance();
    MessageBNF & msg = m_message.messageBnf;

    // Check arguments count
    if (msg.arguments.size() != 4 || msg.arguments[3] == ":") {
        result.m_replies.push_back(Message("461 " + m_message.m_from->getNick() + " USER :Not enough parameters", m_message.m_from));
        return result;
    }


    const std::string & user_name = msg.arguments[0];
    const std::string & real_name = msg.arguments[3].substr(1, msg.arguments[3].size() - 1);

    User::Ptr user = app_data->users[m_message.m_from->getSockFd()];

    user->setUserName(user_name);
    user->setRealName(real_name);

    // Check authorized. If false - password was incorrect => interrupt login and disconnect
    if (!user->isAuthorized()) {
        result.m_replies.push_back(Message("464 * :Password incorrect", user));
        result.m_replies.push_back(Message("ERROR :Password incorrect", user));

        app_data->server->appendToDisconnectQueue(user->getSockFd());
        return result;
    }

    // Maybe nickname doesn't correctly set
    if (!isRegisterReady())
        return ft::nullopt;

    result.append(successAuth());
    return result;
}
