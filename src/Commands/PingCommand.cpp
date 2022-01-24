//
// Created by ukio on 1/24/22.
//

#include "PingCommand.hpp"

PingCommand::PingCommand() {}

PingCommand::PingCommand(const PingCommand &other) {}

PingCommand &PingCommand::operator=(const PingCommand &other) {
    if (&other == this)
        return *this;

    return *this;
}

PingCommand::~PingCommand() {

}

std::vector<MessageBNF> PingCommand::exec() {
    std::vector<MessageBNF> result;

    return result;
}
