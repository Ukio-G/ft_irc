#ifndef DIECOMMAND_HPP
#define DIECOMMAND_HPP

#include "src/Commands/ClientMessage.hpp"

class DieCommand : public ClientMessage {
public:
    DieCommand();

    DieCommand(const DieCommand &other);

    DieCommand(const Message &message);

    DieCommand &operator=(const DieCommand &other);

    ~DieCommand();

    ft::optional<ServerResponse> exec();
};


#endif
