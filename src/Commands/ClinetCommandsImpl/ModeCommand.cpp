#include "ModeCommand.hpp"

ModeCommand::ModeCommand() {}

ModeCommand::ModeCommand(const ModeCommand &other) : ClientMessage((ClientMessage&)other) {}

ModeCommand &ModeCommand::operator=(const ModeCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

ModeCommand::ModeCommand(const Message &message) : ClientMessage(message) {}

ModeCommand::~ModeCommand() {

}

ft::optional<ServerResponse> ModeCommand::exec() {
    return ft::nullopt;
}
