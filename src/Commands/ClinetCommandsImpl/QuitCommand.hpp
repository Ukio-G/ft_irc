#ifndef QUITCOMMAND_HPP
#define QUITCOMMAND_HPP

#include <src/Commands/ClientMessage.hpp>

class QuitCommand : public ClientMessage {
public:
    QuitCommand();

    QuitCommand(const QuitCommand &other);

    QuitCommand(const Message &message);

    QuitCommand &operator=(const QuitCommand &other);

    ~QuitCommand();

    virtual ft::optional<ServerResponse> exec();
};


#endif
