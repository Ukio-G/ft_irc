#ifndef JOINCOMMAND_HPP
#define JOINCOMMAND_HPP

#include <src/Commands/ClientMessage.hpp>

class JoinCommand : public ClientMessage {
public:
    typedef ft::shared_ptr<JoinCommand> Ptr;

    JoinCommand();

    JoinCommand(const JoinCommand &other);

    JoinCommand(const Message &message);

    JoinCommand &operator=(const JoinCommand &other);

    ~JoinCommand();

    ft::optional<ServerResponse> exec();
};


#endif
