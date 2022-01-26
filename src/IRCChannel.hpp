#ifndef IRCCHANNEL_HPP
#define IRCCHANNEL_HPP


#include <string>
#include <vector>
#include <src/Message/Message.hpp>
#include <optional.hpp>
#include "User.hpp"

class IRCChannel {
public:
    IRCChannel(const std::string &channelName, User::Ptr channelCreator);

    typedef ft::shared_ptr<IRCChannel> Ptr;

    IRCChannel();

    IRCChannel(const IRCChannel &other);

    IRCChannel &operator=(const IRCChannel &other);

    ~IRCChannel();

    std::string channelName;
    std::vector<User::Ptr> users;
    std::vector<User::Ptr> operators;

    std::vector<Message> generateMessage(const std::string & str, User::Ptr from, bool skip_sender = false);
    std::vector<Message> generateUsersList(User::Ptr to);
    ft::optional<Message> appendUser(User::Ptr newUser);
};


#endif
