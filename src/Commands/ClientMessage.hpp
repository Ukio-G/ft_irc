#ifndef CLIENTMESSAGE_HPP
#define CLIENTMESSAGE_HPP

#include <string>
#include <vector>
#include <shared_ptr.hpp>
#include <src/User.hpp>
#include <optional.hpp>
#include <src/Server/ServerResponse.hpp>
#include <src/Message/Message.hpp>

class ClientMessage {
public:
    typedef ft::shared_ptr<ClientMessage> Ptr;
    ClientMessage();

    ClientMessage(const ClientMessage &other);
    ClientMessage(const Message & message);
    ClientMessage &operator=(const ClientMessage &other);

    virtual ~ClientMessage();

    virtual ft::optional<ServerResponse> exec() = 0;
    Message m_message;
};


#endif
