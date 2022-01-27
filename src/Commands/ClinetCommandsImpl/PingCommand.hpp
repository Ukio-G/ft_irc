#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP

#include <optional.hpp>
#include "src/Commands/ClientMessage.hpp"

class PingCommand : public ClientMessage {
public:
    PingCommand();

    PingCommand(const PingCommand &other);

    PingCommand(const Message &message);

    PingCommand &operator=(const PingCommand &other);

    ~PingCommand();

    ft::optional<ServerResponse> exec();
};


#endif
