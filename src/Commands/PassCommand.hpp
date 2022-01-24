#ifndef PASSCOMMAND_HPP
#define PASSCOMMAND_HPP


#include "Command.hpp"

class PassCommand : public Command {
public:
    PassCommand();

    PassCommand(const PassCommand &other);

    PassCommand(const MessageBNF &messageBnf, int sock_source);

    PassCommand &operator=(const PassCommand &other);

    ~PassCommand();

private:
    std::vector<MessageBNF> exec();
};


#endif
