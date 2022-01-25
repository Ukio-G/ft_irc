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

private:
    ft::optional<ServerResponse> exec();
};


#endif
