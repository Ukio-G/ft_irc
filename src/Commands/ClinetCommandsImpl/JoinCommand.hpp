//
// Created by ukio on 1/26/22.
//

#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP


#include <src/Commands/ClientMessage.hpp>

class JoinCommand : public ClientMessage {
public:
    JoinCommand();

    JoinCommand(const JoinCommand &other);

    JoinCommand(const Message &message);

    JoinCommand &operator=(const JoinCommand &other);

    ~JoinCommand();

    ft::optional<ServerResponse> exec();
private:
};


#endif
