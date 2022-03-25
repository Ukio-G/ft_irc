//
// Created by ukio on 1/29/22.
//

#include "NoticeCommand.hpp"
#include "PrivmsgCommand.hpp"

NoticeCommand::NoticeCommand() {}

NoticeCommand::NoticeCommand(const NoticeCommand &other) : ClientMessage((ClientMessage&)other) {}

NoticeCommand &NoticeCommand::operator=(const NoticeCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

NoticeCommand::~NoticeCommand() {

}

NoticeCommand::NoticeCommand(const Message &message) : ClientMessage(message) {}

ft::optional<ServerResponse> NoticeCommand::exec() {
    PrivmsgCommand priv(m_message);
    ft::optional<ServerResponse> result = priv.exec();
    if (result)
        for (size_t i = 0; (*result).m_replies.size() > i; i++)
            (*result).m_replies[i].messageBnf.command = "NOTICE";
    return result;
}
