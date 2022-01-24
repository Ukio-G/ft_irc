#ifndef NICKCOMMAND_HPP
#define NICKCOMMAND_HPP


#include "Command.hpp"

class NickCommand : public Command {
public:
    NickCommand();

    NickCommand(const NickCommand &other);

    NickCommand(const MessageBNF &messageBnf, int sock_source);

    NickCommand &operator=(const NickCommand &other);

    ~NickCommand();

private:
    std::vector<MessageBNF> exec();
};


#endif
