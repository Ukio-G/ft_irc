#ifndef PARTCOMMAND_HPP
#define PARTCOMMAND_HPP


#include <src/Commands/ClientMessage.hpp>

class PartCommand : public ClientMessage {
public:
    typedef ft::shared_ptr<PartCommand> Ptr;

    PartCommand();

    PartCommand(const PartCommand &other);

    PartCommand(const Message & msg);

    PartCommand &operator=(const PartCommand &other);

    ~PartCommand();

    ft::optional<ServerResponse> exec();
};


#endif
