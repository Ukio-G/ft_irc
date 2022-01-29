#ifndef UNDEFINEDCOMMAND_HPP
#define UNDEFINEDCOMMAND_HPP


#include <src/Message/Message.hpp>
#include "ClientMessage.hpp"

class UndefinedCommand : public ClientMessage {
public:
    UndefinedCommand();

    UndefinedCommand(const UndefinedCommand &other);

    UndefinedCommand(const Message &message);

    UndefinedCommand &operator=(const UndefinedCommand &other);

    ~UndefinedCommand();

    virtual ft::optional<ServerResponse> exec();

private:
};


#endif
