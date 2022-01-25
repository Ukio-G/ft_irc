#include "Message.hpp"

Message::Message() {}

Message::Message(const Message &other) : messageBnf(other.messageBnf), m_to(other.m_to), m_from(other.m_from) { }

Message::Message(const MessageBNF &msg_bnf, User::Ptr to, User::Ptr from) : messageBnf(msg_bnf), m_to(to), m_from(from) { }

Message::Message(const std::string &str, User::Ptr to, User::Ptr from) : messageBnf(str), m_to(to), m_from(from) { }

Message &Message::operator=(const Message &other) {
    if (&other == this)
        return *this;
    messageBnf = other.messageBnf;
    m_to = other.m_to;
    m_from = other.m_from;
    return *this;
}

Message::~Message() { }

