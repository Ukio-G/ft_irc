#ifndef USERCOMMAND_HPP
#define USERCOMMAND_HPP


#include "Command.hpp"

class UserCommand : public Command {
public:
    UserCommand();

    UserCommand(const UserCommand &other);

    UserCommand(const MessageBNF &messageBnf, int sock_source);

    UserCommand &operator=(const UserCommand &other);

    ~UserCommand();

    std::vector<MessageBNF> exec();
private:
};


#endif
