#include <src/IRCChannel.hpp>
#include <src/ApplicationData.hpp>
#include <utils.hpp>
#include "ModeCommand.hpp"

ModeCommand::ModeCommand() : channel(0), userArg(0) {}

ModeCommand::ModeCommand(const ModeCommand &other) : ClientMessage((ClientMessage&)other),
channel(other.channel), userArg(0) {}

ModeCommand &ModeCommand::operator=(const ModeCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    channel = other.channel;
    userArg = other.userArg;
    return *this;
}

ModeCommand::ModeCommand(const Message &message) : ClientMessage(message), channel(0), userArg(0) {}

ModeCommand::~ModeCommand() {

}

ft::optional<ServerResponse> ModeCommand::exec() {
    // request: MODE #2 +-bv nick
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
    channel = chIt->second;
    // Check current user (which send command to server) is an operator on the channel
    if (!channel->isChannelOperator(m_message.m_from)) {
        // TODO: Error: User not an operator
        return result;
    }

    // Check user we want affect mode exist on the server
    ft::optional<User::Ptr> user_opt = app_data->getUserByNick(m_message.messageBnf.arguments[2]);
    if (!user_opt.has_value())
    {
        // TODO: Error: User not exist on the channel
        return result;
    }

    userArg = *user_opt;
    handleMode();
    result.append(channel->generateMessage((std::string)m_message.messageBnf, m_message.m_from));
    return result;
}

ft::optional<Message> ModeCommand::handleMode() {
    ApplicationData::Ptr app_data = ApplicationData::instance();

    char modeChar = m_message.messageBnf.arguments[1][0];

    ft::optional<Message> result = ft::nullopt;

    if (modeChar != '+' && modeChar != '-')
        return result;

    bool isAppendMode = (modeChar == '+');

    char mode = m_message.messageBnf.arguments[1][1];

    // Check user we want to affect mode on the channel
    if (!channel->isUserAvailable(userArg)) {
        // TODO: Error: User not exist on the channel, but if we are not try to remove user from ban list
        if (modeChar != '-' && mode != 'b') {
            return result;
        }
    }

    switch (mode) {
        case 'b':
            handleBanMode(isAppendMode);
            break;
        case 'o':
            handleOperatorMode(isAppendMode);
            break;
    }

    return result;
}

void ModeCommand::handleOperatorMode(bool isAppendMode) {
    if (isAppendMode)
        channel->appendUserAsOperator(userArg);
    else
        channel->removeUserFromOperators(userArg);
}

void ModeCommand::handleBanMode(bool isAppendMode) {
    if (isAppendMode)
        channel->addUserToBanList(userArg);
    else
        channel->removeUserFromBanList(userArg);
}
