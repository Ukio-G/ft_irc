//
// Created by ukio on 1/25/22.
//

#ifndef SERVERRESPONSE_HPP
#define SERVERRESPONSE_HPP


#include <src/Message/Message.hpp>

class ServerResponse {
public:
    ServerResponse();

    ServerResponse(const ServerResponse &other);

    ServerResponse &operator=(const ServerResponse &other);

    ~ServerResponse();

    std::vector<Message> m_replies;

    void append(const std::vector<Message> & messages);
private:
};


#endif
