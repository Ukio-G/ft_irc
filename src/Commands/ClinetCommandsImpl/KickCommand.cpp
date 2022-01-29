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
    // Check first arg is a channel
    if (!ft::is_channel(channelName)) {
        // TODO: Error first arg
        return result;
    }

    channelName = channelName.substr(1, channelName.size() - 1);

    // Check channel exist
    IRCChannel::Iterator chIt = app_data->channels.find(channelName);
    if (chIt == app_data->channels.end())
    {
        // TODO: Error: Channel not exist
        return result;
    }
    IRCChannel::Ptr channel = chIt->second;
    // Check current user (which send command to server) is an operator on the channel
    if (!channel->isChannelOperator(m_message.m_from)) {
        // TODO: Error: User not an operator
        return result;
    }

    // Check user we want to kick exist on the server
    ft::optional<User::Ptr> user_opt = app_data->getUserByNick(m_message.messageBnf.arguments[1]);
    if (!user_opt.has_value())
    {
        // TODO: Error: User not exist on the channel
        return result;
    }

    // Check user we want to kick on the channel
    if (!channel->isUserAvailable(*user_opt)) {
        // TODO: Error: User not exist on the channel
        return result;
    }

    // Generate server replies for each user
    std::vector<Message> msgsVector;
    msgsVector = channel->generateMessage("KICK #" + channelName + " " + (*user_opt)->getNick() + " :Kick", m_message.m_from);
    result.append(msgsVector);

    channel->removeUser(*user_opt);

    return result;
}
