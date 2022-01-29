#include "CommandFactory.hpp"
#include <src/Commands/ClinetCommandsImpl/JoinCommand.hpp>
#include <src/Commands/ClinetCommandsImpl/PrivmsgCommand.hpp>
#include <src/Commands/ClinetCommandsImpl/OperCommand.hpp>
#include <src/Commands/ClinetCommandsImpl/KickCommand.hpp>
#include <src/Commands/ClinetCommandsImpl/QuitCommand.hpp>
#include <src/Commands/ClinetCommandsImpl/PartCommand.hpp>
#include "src/Commands/ClinetCommandsImpl/CapCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/PassCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/NickCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/UserCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/DieCommand.hpp"
#include "src/Commands/ClinetCommandsImpl/PingCommand.hpp"
#include <src/Commands/ClinetCommandsImpl/ModeCommand.hpp>

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
    if (messageBNF.command == "DIE")
        result = new DieCommand(msg);
    if (messageBNF.command == "PING")
        result = new PingCommand(msg);
    if (messageBNF.command == "JOIN")
        result = new JoinCommand(msg);
    if (messageBNF.command == "PRIVMSG")
        result = new PrivmsgCommand(msg);
    if (messageBNF.command == "OPER")
        result = new OperCommand(msg);
    if (messageBNF.command == "KICK")
        result = new KickCommand(msg);
    if (messageBNF.command == "QUIT")
        result = new QuitCommand(msg);
    if (messageBNF.command == "PART")
        result = new PartCommand(msg);
    if (messageBNF.command == "MODE")
        result = new ModeCommand(msg);

    return ClientMessage::Ptr(result);
}
