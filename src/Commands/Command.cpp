#include "Command.hpp"
#include "utils/utils.hpp"

Command::Command() {}

Command::Command(const Command &other) : m_message(other.m_message) {}

Command &Command::operator=(const Command &other) {
    if (&other == this)
        return *this;
    m_message = other.m_message;
    return *this;
}

Command::~Command() { }

const MessageBNF &Command::getMMessage() const {
    return m_message;
}

Command::Command(const MessageBNF &messageBnf, int sock_source) : m_message(messageBnf), m_sockSource(sock_source) { }

int Command::getMSockSource() const {
    return m_sockSource;
}

MessageBNF::MessageBNF() {

}

MessageBNF::MessageBNF(const std::string &string) {
    std::vector<std::string> cmd_parts = ft::split(string, ' ');
    size_t cmd_idx = 0;
    if (cmd_parts.empty())
        throw std::runtime_error("Fail to parse command");
    if (cmd_parts[0][0] == ':')
        prefix = cmd_parts[cmd_idx++];
    command = cmd_parts[cmd_idx++];
    arguments.insert(arguments.begin(), cmd_parts.begin() + cmd_idx, cmd_parts.end());
}

MessageBNF::operator std::string() {
    std::string result = prefix + " " + command;
    for (int i = 0; i < arguments.size(); ++i)
        result += (" " + arguments[i]);
    return result;
}

MessageBNF::MessageBNF(const MessageBNF & other) : prefix(other.prefix), command(other.command), arguments(other.arguments) { }

MessageBNF &MessageBNF::operator=(const MessageBNF &other) {
    if (&other == this)
        return *this;

    prefix = other.prefix;
    command = other.command;
    arguments = other.arguments;

    return *this;
}
