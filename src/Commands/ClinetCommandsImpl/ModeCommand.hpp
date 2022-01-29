#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP

#include <src/Server/ServerResponse.hpp>
#include <optional.hpp>
#include <src/Commands/ClientMessage.hpp>
#include <src/IRCChannel.hpp>

class ModeCommand : public ClientMessage {
public:
    typedef ft::shared_ptr<ModeCommand> Ptr;

    ModeCommand();

    ModeCommand(const ModeCommand &other);

    ModeCommand(const Message &message);

    ModeCommand &operator=(const ModeCommand &other);

    ~ModeCommand();

    ft::optional<ServerResponse> exec();

    ft::optional<Message> handleMode();

    void handleOperatorMode(bool isAppendMode);

    void handleBanMode(bool isAppendMode);

private:
    IRCChannel::Ptr channel;
    User::Ptr userArg;
};


#endif
