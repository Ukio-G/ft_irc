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

    if (m_message.messageBnf.arguments.size() == 1)
        return ft::nullopt;

    if (m_message.messageBnf.arguments.size() < 1) {
        result.m_replies.push_back(Message("461 " + m_message.m_from->getNick() + " MODE :Not enough parameters", m_message.m_from));
        return result;
    }

    std::string channelName = m_message.messageBnf.arguments[0];
    std::string userNick = m_message.m_from->getNick();

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

    channel = chIt->second;
    // Check current user (which send command to server) is an operator on the channel
    if (!channel->isChannelOperator(m_message.m_from)) {
        result.m_replies.push_back(Message("482 " + userNick + " #" + channelName + " :You don't have enough channel privileges", m_message.m_from));
        return result;
    }

    // Check user we want affect mode exist on the server
    ft::optional<User::Ptr> user_opt = app_data->getUserByNick(m_message.messageBnf.arguments[2]);
    if (!user_opt.has_value()) {
        std::string non_existed_nick = m_message.messageBnf.arguments[2];
        result.m_replies.push_back(Message("401 " + userNick + " " + non_existed_nick + " :No such nick", m_message.m_from));
        return result;
    }

    // Check user we want affect mode exist on the channel
    if (!channel->isUserAvailable(*user_opt) && !channel->isBanned(*user_opt)) {
        std::string non_existed_nick = m_message.messageBnf.arguments[2];
        result.m_replies.push_back(Message("401 " + userNick + " " + non_existed_nick + " :No such nick", m_message.m_from));
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
