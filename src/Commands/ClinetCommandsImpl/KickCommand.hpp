#ifndef KICKCOMMAND_HPP
#define KICKCOMMAND_HPP


#include <src/Commands/ClientMessage.hpp>

class KickCommand : public ClientMessage {
public:
    KickCommand();

    KickCommand(const KickCommand &other);

    KickCommand &operator=(const KickCommand &other);

    ~KickCommand();

    KickCommand(const Message &message);

    virtual ft::optional<ServerResponse> exec();
};


#endif
