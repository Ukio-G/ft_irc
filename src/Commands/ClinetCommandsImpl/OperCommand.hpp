#ifndef OPERCOMMAND_HPP
#define OPERCOMMAND_HPP

#include <src/Commands/ClientMessage.hpp>

class OperCommand : public ClientMessage {
public:
    typedef ft::shared_ptr<OperCommand> Ptr;

    OperCommand();

    OperCommand(const OperCommand &other);

    OperCommand(const Message &message);

    OperCommand &operator=(const OperCommand &other);

    ~OperCommand();

    ft::optional<ServerResponse> exec();
};


#endif
