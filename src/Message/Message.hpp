#ifndef MESSAGE_HPP
#define MESSAGE_HPP


#include <src/User.hpp>
#include "MessageBNF.hpp"

class Message {
public:
    Message();

    Message(const Message &other);
    Message(const MessageBNF &msg_bnf, User::Ptr to = User::Ptr(0), User::Ptr from = User::Ptr(0));

    Message(const std::string &str, User::Ptr to = User::Ptr(0), User::Ptr from = User::Ptr(0));

    Message &operator=(const Message &other);

    ~Message();

    MessageBNF messageBnf;
    User::Ptr m_to;
    User::Ptr m_from;
private:
};


#endif
