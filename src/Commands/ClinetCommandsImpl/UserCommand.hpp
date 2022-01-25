#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP


#include "src/Commands/ClientMessage.hpp"

class UserCommand : public ClientMessage {
public:
    UserCommand();

    UserCommand(const UserCommand &other);

    UserCommand(const Message &message);

    UserCommand &operator=(const UserCommand &other);

    ~UserCommand();

    ft::optional<ServerResponse> exec();
private:
};


#endif
