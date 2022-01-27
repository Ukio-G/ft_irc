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