#include <src/ApplicationData.hpp>
#include <optional.hpp>
#include "CapCommand.hpp"

CapCommand::CapCommand() {}

CapCommand::CapCommand(const CapCommand &other) : ClientMessage((ClientMessage&)other) {}

CapCommand &CapCommand::operator=(const CapCommand &other) {
    if (&other == this)
        return *this;
    ClientMessage::operator=((ClientMessage&)other);
    return *this;
}

CapCommand::~CapCommand() { }

ft::optional<ServerResponse> CapCommand::exec() {
    ServerResponse result;
    ApplicationData::Ptr appdata = ApplicationData::instance();

    if (m_message.messageBnf.arguments[0] == "LS") {
        appdata->lockedCap.insert(m_message.m_from->getSockFd());
        Message msg(MessageBNF("CAP * LS :"), m_message.m_from);
        result.m_replies.push_back(msg);
    }

    if (m_message.messageBnf.arguments[0] == "END") {
        appdata->lockedCap.erase(m_message.m_from->getSockFd());
    }

    return result;
}

CapCommand::CapCommand(const Message &msg) : ClientMessage(msg) { }
