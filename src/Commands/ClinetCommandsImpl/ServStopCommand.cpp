//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "ServStopCommand.hpp"

ServStopCommand::ServStopCommand() {}

ServStopCommand::ServStopCommand(const ServStopCommand &other) : ClientMessage((ClientMessage&)other) {}

ServStopCommand &ServStopCommand::operator=(const ServStopCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

ServStopCommand::ServStopCommand(const Message &message) : ClientMessage(message) {}

ServStopCommand::~ServStopCommand() { }

ft::optional<ServerResponse> ServStopCommand::exec() {
    ApplicationData::Ptr appdata = ApplicationData::instance();

    appdata->server->stop();

    return ft::optional<ServerResponse>();
}