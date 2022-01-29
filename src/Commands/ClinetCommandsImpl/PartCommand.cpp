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

    // Input: PART #1 :https://quassel-irc.org - Chat comfortably. Anywhere.
    if (!ft::is_channel(m_message.messageBnf.arguments[0])) {
        // TODO: Argument is not a channel
        return result;
    }
    std::string channelName = m_message.messageBnf.arguments[0];
    channelName = channelName.substr(1, channelName.size() - 1);

    // Check channel exist
    if (app_data->channels.find(channelName) == app_data->channels.end()) {
        // TODO: No such channel
        return result;
    }

    IRCChannel::Ptr channel = app_data->channels[channelName];

    // Check user joined in the channel
    if (!channel->isUserAvailable(m_message.m_from)) {
        // TODO: User not in the channel
        return result;
    }


    std::string cmd_str = "PART " + m_message.messageBnf.arguments[0];
    if (m_message.messageBnf.arguments.size() > 1)
        cmd_str += " " + m_message.messageBnf.arguments[1];     // If user add message to PART command

    result.append(channel->generateMessage(cmd_str, m_message.m_from));

    channel->removeUser(m_message.m_from);

    // Reply for each: :nick!~userA@192.168.0.87 PART #1 :https://quassel-irc.org - Chat comfortably. Anywhere.
    return result;
}
