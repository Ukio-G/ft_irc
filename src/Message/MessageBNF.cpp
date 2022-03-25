#include <stdexcept>
#include <utils.hpp>
#include "MessageBNF.hpp"

MessageBNF::MessageBNF() : terminator("\x0d\x0a") { }

MessageBNF::MessageBNF(const std::string &string) : terminator("\x0d\x0a") {
    std::vector<std::string> cmd_parts = ft::split(string, ' ');
    size_t cmd_idx = 0;
    if (cmd_parts.empty())
        throw std::runtime_error("Fail to parse command");
    if (cmd_parts[0][0] == ':')
        prefix = cmd_parts[cmd_idx++];
    command = cmd_parts[cmd_idx++];
    arguments.insert(arguments.begin(), cmd_parts.begin() + cmd_idx, cmd_parts.end());
}

MessageBNF::operator std::string() const{
    std::string result;
    if (!prefix.empty())
        result += prefix + " ";
    if (!command.empty())
        result += command;
    for (size_t i = 0; i < arguments.size(); ++i)
        result += (" " + arguments[i]);
    result += terminator;
    return result;
}

MessageBNF::MessageBNF(const MessageBNF & other) : prefix(other.prefix), command(other.command), arguments(other.arguments), terminator("\x0d\x0a") { }

MessageBNF &MessageBNF::operator=(const MessageBNF &other) {
    if (&other == this)
        return *this;

    prefix = other.prefix;
    command = other.command;
    arguments = other.arguments;
    terminator = other.terminator;

    return *this;
}