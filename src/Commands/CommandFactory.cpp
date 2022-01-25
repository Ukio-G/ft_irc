//
// Created by ukio on 1/24/22.
//

#include "CommandFactory.hpp"
#include "src/Commands/ClinetCommandsImpl/CapCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/PassCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/NickCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/UserCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/ServStopCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/PingCommand.hpp"

CommandFactory::CommandFactory() {}

CommandFactory::CommandFactory(const CommandFactory &other) {}

CommandFactory::~CommandFactory() {}

ClientMessage::Ptr CommandFactory::createCommand(const Message & msg) {
    ClientMessage * result = 0;

    MessageBNF messageBNF(msg.messageBnf);

    if (messageBNF.command == "CAP")
        result = new CapCommand(msg);
    if (messageBNF.command == "PASS")
        result = new PassCommand(msg);
    if (messageBNF.command == "NICK")
        result = new NickCommand(msg);
    if (messageBNF.command == "USER")
        result = new UserCommand(msg);
    if (messageBNF.command == "SERVSTOP")
        result = new ServStopCommand(msg);
    if (messageBNF.command == "PING")
        result = new PingCommand(msg);

    return ClientMessage::Ptr(result);
}
