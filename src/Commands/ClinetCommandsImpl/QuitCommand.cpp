//
// Created by ukio on 1/27/22.
//

#include <src/ApplicationData.hpp>
#include <algorithm>
#include "QuitCommand.hpp"

QuitCommand::QuitCommand() {}

QuitCommand::QuitCommand(const QuitCommand &other) : ClientMessage(other) { }

QuitCommand::QuitCommand(const Message &message) : ClientMessage(message) { }

QuitCommand &QuitCommand::operator=(const QuitCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

QuitCommand::~QuitCommand() { }

ft::optional<ServerResponse> QuitCommand::exec() {
    ServerResponse response;
    ApplicationData::Ptr app_data = ApplicationData::instance();

    // Send to all users in one channel with this QUIT msg
    std::vector<IRCChannel::Ptr> channels = ApplicationData::userChannels(m_message.m_from);
    std::string quitMessage = "QUIT :Quit: Quit";

    for (int i = 0; i < channels.size(); ++i) {
        std::vector<Message> messages = channels[i]->generateMessage(quitMessage, m_message.m_from, true);
        response.m_replies.insert(response.m_replies.end(), messages.begin(), messages.end());
    }
//    quitMessage += "\x0d\x0a";
//    quitMessage += "ERROR :Quit: Quit";

    response.m_replies.push_back(Message(quitMessage, m_message.m_from, m_message.m_from));
    response.m_replies.push_back(Message("ERROR :Quit: Quit", m_message.m_from));
    app_data->server->appendToDisconnectQueue(m_message.m_from->getSockFd());

    return response;
}

