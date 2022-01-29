#ifndef IRCCHANNEL_HPP
#define IRCCHANNEL_HPP


#include <string>
#include <vector>
#include <src/Message/Message.hpp>
#include <optional.hpp>
#include <map>
#include <set>
#include "User.hpp"

class IRCChannel {
    struct Flags {
    };
public:
    IRCChannel(const std::string &channelName, User::Ptr channelCreator);
    typedef std::set<User::Ptr>::iterator uIt_t;

    typedef ft::shared_ptr<IRCChannel> Ptr;
    typedef std::map<std::string, Ptr>::iterator Iterator;

    IRCChannel();

    IRCChannel(const IRCChannel &other);

    IRCChannel &operator=(const IRCChannel &other);

    ~IRCChannel();

    std::string channelName;
    std::set<User::Ptr> users;
    std::set<User::Ptr> operators;
    std::set<std::string> banned;

    std::vector<Message> generateMessage(const std::string & str, User::Ptr from, bool skip_sender = false);
    std::vector<Message> generateUsersList(User::Ptr to);
    ft::optional<Message> appendUser(User::Ptr newUser);
    ft::optional<Message> appendUserAsOperator(User::Ptr newUser);
    ft::optional<Message> removeUserFromOperators(User::Ptr newUser);
    ft::optional<Message> addUserToBanList(User::Ptr newUser);
    ft::optional<Message> removeUserFromBanList(User::Ptr newUser);

    bool isUserAvailable(User::Ptr newUser);
    bool isChannelOperator(User::Ptr newUser);
    void removeUser(User::Ptr user);

    bool isBanned(User::Ptr user);
};


#endif
