//
// Created by ukio on 1/25/22.
//

#include "ServerResponse.hpp"

ServerResponse::ServerResponse() {}

ServerResponse::ServerResponse(const ServerResponse &other) : m_replies(other.m_replies) {}

ServerResponse &ServerResponse::operator=(const ServerResponse &other) {
    if (&other == this)
        return *this;
    m_replies = other.m_replies;
    return *this;
}

ServerResponse::~ServerResponse() { }

void ServerResponse::append(const std::vector<Message> &messages) {
    m_replies.insert(m_replies.end(), messages.begin(), messages.end());
}
