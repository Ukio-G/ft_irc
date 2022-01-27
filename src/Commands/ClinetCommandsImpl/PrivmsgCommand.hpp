#ifndef PRIVMSGCOMMAND_HPP
#define PRIVMSGCOMMAND_HPP


#include <src/Commands/ClientMessage.hpp>

class PrivmsgCommand : public ClientMessage {
public:
    PrivmsgCommand();

    PrivmsgCommand(const PrivmsgCommand &other);

    PrivmsgCommand(const Message &message);

    PrivmsgCommand &operator=(const PrivmsgCommand &other);

    ~PrivmsgCommand();

    ft::optional<ServerResponse> exec();

private:
    std::vector<Message> messageToChannel(const std::string & receiverChannel);

    Message messageToUser(const std::string & receiverUser);
};


#endif
