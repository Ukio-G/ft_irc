cmake_minimum_required(VERSION 3.20)
project(SocketServer)

include_directories(. utils)

set(CMAKE_CXX_STANDARD 98)

add_executable(SocketServer src/main.cpp src/Server/SocketServer.cpp src/Server/SocketServer.hpp src/ApplicationData.cpp src/User.cpp utils/utils.cpp src/Commands/ClientMessage.cpp
        src/IRCChannel.cpp
        src/Commands/CommandsQueue.cpp
        src/Commands/ClinetCommandsImpl/CapCommand.cpp
        src/Commands/CommandFactory.cpp src/Commands/CommandFactory.hpp src/Commands/ClinetCommandsImpl/PassCommand.cpp src/Commands/ClinetCommandsImpl/PassCommand.hpp src/Commands/ClinetCommandsImpl/UserCommand.cpp src/Commands/ClinetCommandsImpl/UserCommand.hpp src/Commands/ClinetCommandsImpl/NickCommand.cpp src/Commands/ClinetCommandsImpl/NickCommand.hpp utils/optional.hpp src/Commands/ClinetCommandsImpl/PingCommand.cpp src/Commands/ClinetCommandsImpl/PingCommand.hpp src/Commands/ClinetCommandsImpl/DieCommand.cpp src/Commands/ClinetCommandsImpl/DieCommand.hpp src/Message/Message.cpp src/Message/Message.hpp src/Message/MessageBNF.cpp src/Message/MessageBNF.hpp src/Server/ServerResponse.cpp src/Server/ServerResponse.hpp src/Server/ServerStatus.cpp src/Server/ServerStatus.hpp src/Commands/ClinetCommandsImpl/JoinCommand.cpp src/Commands/ClinetCommandsImpl/JoinCommand.hpp src/Commands/ClinetCommandsImpl/PrivmsgCommand.cpp src/Commands/ClinetCommandsImpl/PrivmsgCommand.hpp src/Commands/ClinetCommandsImpl/ModeCommand.cpp src/Commands/ClinetCommandsImpl/ModeCommand.hpp src/Commands/ClinetCommandsImpl/OperCommand.cpp src/Commands/ClinetCommandsImpl/OperCommand.hpp src/Commands/ClinetCommandsImpl/KickCommand.cpp src/Commands/ClinetCommandsImpl/KickCommand.hpp src/Commands/ClinetCommandsImpl/QuitCommand.cpp src/Commands/ClinetCommandsImpl/QuitCommand.hpp src/Commands/ClinetCommandsImpl/PartCommand.cpp src/Commands/ClinetCommandsImpl/PartCommand.hpp src/Commands/ClinetCommandsImpl/NoticeCommand.cpp src/Commands/ClinetCommandsImpl/NoticeCommand.hpp)
