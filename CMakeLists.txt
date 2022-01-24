cmake_minimum_required(VERSION 3.20)
project(SocketServer)

include_directories(. utils)

set(CMAKE_CXX_STANDARD 98)

add_executable(SocketServer src/main.cpp src/SocketServer.cpp src/SocketServer.hpp src/ApplicationData.cpp src/User.cpp utils/utils.cpp src/Commands/Command.cpp
        src/Commands/CommandsHandler.cpp
        src/Commands/CapCommand.cpp
        src/Commands/CommandFactory.cpp src/Commands/CommandFactory.hpp src/Commands/PassCommand.cpp src/Commands/PassCommand.hpp src/Commands/UserCommand.cpp src/Commands/UserCommand.hpp src/Commands/NickCommand.cpp src/Commands/NickCommand.hpp utils/optional.hpp src/Commands/PingCommand.cpp src/Commands/PingCommand.hpp)
