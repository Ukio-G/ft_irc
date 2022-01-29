#include "PartCommand.hpp"
#include <utils/utils.hpp>
#include <src/ApplicationData.hpp>

PartCommand::PartCommand() {}

PartCommand::PartCommand(const PartCommand &other) : ClientMessage((ClientMessage&)other) {}

PartCommand &PartCommand::operator=(const PartCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

PartCommand::~PartCommand() { }

PartCommand::PartCommand(const Message &msg) : ClientMessage(msg) { }

ft::optional<ServerResponse> PartCommand::exec() {
    ServerResponse result;
    ApplicationData::Ptr app_data = ApplicationData::instance();

    std::string channelName = m_message.messageBnf.arguments[0];
    std::string userNick = m_message.m_from->getNick();

    // Check arguments count
    if (m_message.messageBnf.arguments.size() < 1) {
        result.m_replies.push_back(Message("461 " + m_message.m_from->getNick() + " PART :Not enough parameters", m_message.m_from));
        return result;
    }

    // Check channel is correct (# is first letter of channel name)
    if (!ft::is_channel(channelName)) {
        result.m_replies.push_back(Message("403 " + userNick + " " + channelName + " :No such channel", m_message.m_from));
        return result;
    }

    channelName = channelName.substr(1, channelName.size() - 1);

    // Check channel exist
    if (app_data->channels.find(channelName) == app_data->channels.end()) {
        result.m_replies.push_back(Message("403 " + userNick + " #" + channelName + " :No such channel", m_message.m_from));
        return result;
    }

    IRCChannel::Ptr channel = app_data->channels[channelName];

    // Check user joined in the channel
    if (!channel->isUserAvailable(m_message.m_from)) {
        result.m_replies.push_back(Message("442 " + userNick + " #" + channelName + " :You're not on that channel", m_message.m_from));
        return result;
    }

    // Generate command for each channel user
    std::string cmd_str = "PART " + m_message.messageBnf.arguments[0];
    if (m_message.messageBnf.arguments.size() > 1)
        cmd_str += " " + m_message.messageBnf.arguments[1];     // If user add message to PART command

    result.append(channel->generateMessage(cmd_str, m_message.m_from));

    // Remove user from channel
    channel->removeUser(m_message.m_from);

    return result;
}
