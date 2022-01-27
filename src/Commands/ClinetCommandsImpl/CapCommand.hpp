#ifndef CAPCOMMAND_HPP
#define CAPCOMMAND_HPP

#include "src/Commands/ClientMessage.hpp"

class CapCommand : public ClientMessage {
public:
    typedef ft::shared_ptr<CapCommand> Ptr;

    CapCommand();

    CapCommand(const CapCommand &other);

    CapCommand(const Message & msg);

    CapCommand &operator=(const CapCommand &other);

    ~CapCommand();

    ft::optional<ServerResponse> exec();
};


#endif
