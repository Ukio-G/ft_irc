#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP


#include "src/Commands/ClientMessage.hpp"

class PassCommand : public ClientMessage {
public:
    PassCommand();

    PassCommand(const PassCommand &other);

    PassCommand(const Message &message);

    PassCommand &operator=(const PassCommand &other);

    ~PassCommand();

private:
    ft::optional<ServerResponse> exec();
};


#endif
