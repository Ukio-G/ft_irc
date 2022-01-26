#include <src/ApplicationData.hpp>
#include <utils.hpp>
#include "PrivmsgCommand.hpp"

PrivmsgCommand::PrivmsgCommand() { }

PrivmsgCommand::PrivmsgCommand(const PrivmsgCommand &other) : ClientMessage((ClientMessage&)other) { }

PrivmsgCommand &PrivmsgCommand::operator=(const PrivmsgCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

PrivmsgCommand::PrivmsgCommand(const Message &message) : ClientMessage(message) { }

PrivmsgCommand::~PrivmsgCommand() { }

Message PrivmsgCommand::messageToUser(const std::string & receiverUser) {
    ApplicationData::Ptr app_data = ApplicationData::instance();

    ft::optional<User::Ptr> to_opt = app_data->getUserByNick(receiverUser);
    if (to_opt.has_value() == false) {
        //TODO: Handle no such user
    }


    std::string msg_str = ":" + m_message.m_from->generateFullUsername() + " PRIVMSG " + receiverUser;

    for (int i = 1; i < m_message.messageBnf.arguments.size(); ++i)
        msg_str += m_message.messageBnf.arguments[i] + " ";
    
    Message msg( msg_str, *to_opt);
    return msg;
}

std::vector<Message> PrivmsgCommand::messageToChannel(const std::string & receiverChannel) {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    std::vector<Message> result;
    typedef std::map<std::string, IRCChannel::Ptr>::iterator chIt;
    std::string channel = receiverChannel.substr(1, receiverChannel.size()- 1);
    chIt channelIt = app_data->channels.find(channel);
    if (channelIt == app_data->channels.end()) {
        //TODO: Handle no such channel
    }

    std::string msg_str = "PRIVMSG #" + channel + " ";//  + m_message.messageBnf.arguments.back();

    for (int i = 1; i < m_message.messageBnf.arguments.size(); ++i)
        msg_str += m_message.messageBnf.arguments[i] + " ";

    result = channelIt->second->generateMessage(msg_str, m_message.m_from, true);

    return result;
}

ft::optional<ServerResponse> PrivmsgCommand::exec() {
    ServerResponse result;

    ApplicationData::Ptr app_data = ApplicationData::instance();

    std::vector<std::string> receivers = ft::split(m_message.messageBnf.arguments[0], ',');

    for (int i = 0; i < receivers.size(); ++i) {
        bool toChannel = receivers[i][0] == '#';
        if (toChannel) {
            std::vector<Message> messages = messageToChannel(receivers[i]);
            result.m_replies.insert(result.m_replies.end(), messages.begin(), messages.end());
        }
        else
            result.m_replies.push_back(messageToUser(receivers[i]));
    }

    return result;
}
