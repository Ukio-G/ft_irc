#include <src/ApplicationData.hpp>
#include "JoinCommand.hpp"

JoinCommand::JoinCommand() {}

JoinCommand::JoinCommand(const JoinCommand &other) : ClientMessage((ClientMessage&)other) {}

JoinCommand::JoinCommand(const Message &message) : ClientMessage(message) {}

JoinCommand &JoinCommand::operator=(const JoinCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

JoinCommand::~JoinCommand() { }

ft::optional<ServerResponse> JoinCommand::exec() {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    ServerResponse response;

    std::string channelName = m_message.messageBnf.arguments[0].substr(1, m_message.messageBnf.arguments[0].size() - 1);
    // Maybe we are created channel?

    bool isChannelExist = app_data->channels.find(channelName) != app_data->channels.end();

    if (isChannelExist) {
        ft::optional<Message> appendResult = app_data->channels[channelName]->appendUser(m_message.m_from);
        if (appendResult.has_value()) { // If appendResult has value, something was wrong, and appendResult contain error message
            response.m_replies.push_back(*appendResult);
            return response;
        }
    } else {
        IRCChannel * new_channel = new IRCChannel(channelName, m_message.m_from);
        app_data->channels[channelName] = new_channel;
    }
    // Notify all current users in channel
    std::vector<Message> channelReplies = app_data->channels[channelName]->generateUsersList(m_message.m_from);

    std::string joinMessage = "JOIN #" + channelName;
    std::vector<Message> joinMessages = app_data->channels[channelName]->generateMessage(joinMessage, m_message.m_from);

    response.m_replies.insert(response.m_replies.end(), joinMessages.begin(), joinMessages.end());
    response.m_replies.insert(response.m_replies.end(), channelReplies.begin(), channelReplies.end());

    return response;
}
