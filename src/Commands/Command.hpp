#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <shared_ptr.hpp>

class MessageBNF {
public:
    MessageBNF();
    MessageBNF(const std::string & string);
    explicit MessageBNF(const MessageBNF& string);
    operator std::string();

    MessageBNF& operator=(const MessageBNF& other);

    std::string prefix;
    std::string command;
    std::vector<std::string> arguments;
};

class Command {
public:
    typedef ft::shared_ptr<Command> Ptr;
    Command();
    Command(const MessageBNF &messageBnf, int sock_source);

    Command(const Command &other);

    Command &operator=(const Command &other);

    virtual ~Command();

    virtual std::vector<MessageBNF> exec() = 0;

protected:
    int m_sockSource;
public:
    int getMSockSource() const;

protected:
    // Answer to
    MessageBNF m_message;
public:
    const MessageBNF &getMMessage() const;
};


#endif
