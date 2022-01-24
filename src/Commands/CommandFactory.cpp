//
// Created by ukio on 1/24/22.
//

#include "CommandFactory.hpp"
#include "CapCommand.hpp"

CommandFactory::CommandFactory() {}

CommandFactory::CommandFactory(const CommandFactory &other) {}

CommandFactory::~CommandFactory() {}

Command::Ptr CommandFactory::createCommand(const std::pair<std::string, int> & clientMessage) {
    MessageBNF messageBNF = MessageBNF(clientMessage.first);
    int sock_fd = clientMessage.second;
    Command * result = 0;

    if (messageBNF.command == "CAP")
        result = new CapCommand(messageBNF, sock_fd);
    if (messageBNF.command == "PASS")
        result = new CapCommand(messageBNF, sock_fd);
    if (messageBNF.command == "NICK")
        result = new CapCommand(messageBNF, sock_fd);
    if (messageBNF.command == "USER")
        result = new CapCommand(messageBNF, sock_fd);

    return Command::Ptr(result);
}
