//
// Created by ukio on 1/24/22.
//

#ifndef PINGCOMMAND_HPP
#define PINGCOMMAND_HPP


#include "Command.hpp"

class PingCommand : public Command {
public:
    PingCommand();

    PingCommand(const PingCommand &other);

    PingCommand &operator=(const PingCommand &other);

    ~PingCommand();

private:
    std::vector<MessageBNF> exec();
};


#endif
