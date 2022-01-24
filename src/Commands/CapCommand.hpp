//
// Created by ukio on 1/24/22.
//

#ifndef CAPCOMMAND_HPP
#define CAPCOMMAND_HPP

#include "Command.hpp"

class CapCommand : public Command {
public:
    typedef ft::shared_ptr<CapCommand> Ptr;

    CapCommand();

    CapCommand(const CapCommand &other);

    CapCommand(const MessageBNF & messageBnf, int sock_source);

    CapCommand &operator=(const CapCommand &other);

    ~CapCommand();

private:
    std::vector<MessageBNF> exec();
};


#endif
