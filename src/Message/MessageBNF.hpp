#ifndef MESSAGEBNF_HPP
#define MESSAGEBNF_HPP

#include <string>
#include <vector>

class MessageBNF {
public:
    MessageBNF();
    explicit MessageBNF(const std::string & string);
    explicit MessageBNF(const MessageBNF& other);
    operator std::string() const;

    MessageBNF& operator=(const MessageBNF& other);

    std::string prefix;
    std::string command;
    std::vector<std::string> arguments;
    std::string terminator;
};


#endif
