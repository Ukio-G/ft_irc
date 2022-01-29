#include <src/ApplicationData.hpp>
#include "KickCommand.hpp"
#include <utils/utils.hpp>

KickCommand::KickCommand() {}

KickCommand::KickCommand(const KickCommand &other) : ClientMessage((ClientMessage&)other) {}

KickCommand &KickCommand::operator=(const KickCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

KickCommand::~KickCommand() { }

KickCommand::KickCommand(const Message &message) : ClientMessage(message) { }

ft::optional<ServerResponse> KickCommand::exec() {
    ServerResponse result;
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::string channelName = m_message.messageBnf.arguments[0];
    std::string userNick = m_message.m_from->getNick();

    // Check arguments count
    if (m_message.messageBnf.arguments.size() < 2) {
        result.m_replies.push_back(Message("461 " + m_message.m_from->getNick() + " KICK :Not enough parameters", m_message.m_from));
        return result;
    }

    // Check first arg is a channel
    if (!ft::is_channel(channelName)) {
        result.m_replies.push_back(Message("403 " + userNick + " " + channelName + " :No such channel", m_message.m_from));
        return result;
    }

    channelName = channelName.substr(1, channelName.size() - 1);

    // Check channel exist
    IRCChannel::Iterator chIt = app_data->channels.find(channelName);
    if (chIt == app_data->channels.end()) {
        result.m_replies.push_back(Message("403 " + userNick + " #" + channelName + " :No such channel", m_message.m_from));
        return result;
    }

    IRCChannel::Ptr channel = chIt->second;
    // Check current user (which send command to server) is an operator on the channel
    if (!channel->isChannelOperator(m_message.m_from)) {
        result.m_replies.push_back(Message("482 " + userNick + " #" + channelName + " :You don't have enough channel privileges", m_message.m_from));
        return result;
    }

    // Check user we want to kick exist on the server
    ft::optional<User::Ptr> user_opt = app_data->getUserByNick(m_message.messageBnf.arguments[1]);
    if (!user_opt.has_value()) {
        std::string non_existed_nick = m_message.messageBnf.arguments[1];
        result.m_replies.push_back(Message("401 " + userNick + " " + non_existed_nick + " :No such nick", m_message.m_from));
        return result;
    }

    // Check user we want to kick on the channel
    if (!channel->isUserAvailable(*user_opt)) {
        std::string non_existed_nick = m_message.messageBnf.arguments[1];
        result.m_replies.push_back(Message("401 " + userNick + " " + non_existed_nick + " :No such nick", m_message.m_from));
        return result;
    }

    // Generate server replies for each user
    std::vector<Message> msgsVector;
    msgsVector = channel->generateMessage("KICK #" + channelName + " " + (*user_opt)->getNick() + " :Kick", m_message.m_from);
    result.append(msgsVector);

    channel->removeUser(*user_opt);

    return result;
}
