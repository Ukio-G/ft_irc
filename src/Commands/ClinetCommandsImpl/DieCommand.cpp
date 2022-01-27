#include <src/ApplicationData.hpp>
#include "DieCommand.hpp"

DieCommand::DieCommand() {}

DieCommand::DieCommand(const DieCommand &other) : ClientMessage((ClientMessage&)other) {}

DieCommand &DieCommand::operator=(const DieCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

DieCommand::DieCommand(const Message &message) : ClientMessage(message) {}

DieCommand::~DieCommand() { }

ft::optional<ServerResponse> DieCommand::exec() {
    ApplicationData::Ptr appdata = ApplicationData::instance();

    if (m_message.m_from->isOperator())
        appdata->server->stop();

    return ft::optional<ServerResponse>();
}