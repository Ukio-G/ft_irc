#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP


#include "src/Commands/ClientMessage.hpp"

class NickCommand : public ClientMessage {
public:
    NickCommand();

    NickCommand(const NickCommand &other);

    NickCommand(const Message &message);

    NickCommand &operator=(const NickCommand &other);

    ~NickCommand();

    ft::optional<ServerResponse> exec();

    std::vector<Message> successAuth();

    bool isRegisterReady();
};


#endif
