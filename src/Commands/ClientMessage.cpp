#include "ClientMessage.hpp"
#include "utils/utils.hpp"

ClientMessage::ClientMessage() {}

ClientMessage::ClientMessage(const ClientMessage &other) {}

ClientMessage &ClientMessage::operator=(const ClientMessage &other) {
    if (&other == this)
        return *this;
    m_message = other.m_message;
    return *this;
}

ClientMessage::~ClientMessage() { }

ClientMessage::ClientMessage(const Message &message) : m_message(message) { }
