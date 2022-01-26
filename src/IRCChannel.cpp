#include <algorithm>
#include "IRCChannel.hpp"
#include "ApplicationData.hpp"

IRCChannel::IRCChannel() {}

IRCChannel::IRCChannel(const std::string & channelName, User::Ptr channelCreator) {
    this->channelName = channelName;
    users.push_back(channelCreator);
    operators.push_back(channelCreator);
}

IRCChannel::IRCChannel(const IRCChannel &other) :
    channelName(other.channelName),
    users(other.users),
    operators(other.operators) {}

IRCChannel &IRCChannel::operator=(const IRCChannel &other) {
    if (&other == this)
        return *this;

    channelName = other.channelName;
    users = other.users;
    operators = other.operators;

    return *this;
}

IRCChannel::~IRCChannel() {

}

/**
 * Generate Message with str content to each user in channel, from user from
 * (str MUST NOT contain prefix like nick!user@host)
 * @param str - command, which will be copied for each user
 * @param from - user from that message will be passed
 * @return vector of message, which will append to ServerResponse object
 */
std::vector<Message> IRCChannel::generateMessage(const std::string &str, User::Ptr from, bool skip_sender) {
    std::vector<Message> result;
    for (int i = 0; i < users.size(); ++i) {
        // TODO: maybe best to implement "from" in sender function (instead of append it's in the start of message)?
        if (skip_sender && users[i]->getNick() == from->getNick())
            continue;
        Message msg = Message(":" + from->generateFullUsername() + " " + str, users[i], from);
        result.push_back(msg);
    }
    return result;
}

/**
 * Replies 353 366 to user @to
 * RPL_NAMREPLY (353) - provides nicks of users, joined in the channel
 */
std::vector<Message> IRCChannel::generateUsersList(User::Ptr to) {
    std::vector<Message> result;
    std::string names;
    for (int i = 0; i < users.size(); ++i) {
        //TODO: Maybe i can optimize this with RBTree (store operators in std::set... and define operator<=> for User[::Ptr])?
        bool isChannelOperator = std::find(operators.begin(), operators.end(), users[i]) != operators.end();

        if (i != 0)             names += " ";
        if (isChannelOperator)  names += "@";

        names += users[i]->getNick();
    }

    std::string serverName = ApplicationData::instance()->serverName;

    Message RPL_NAMTOPIC(":" + serverName + " 332 " + to->getNick() + " #" + channelName + " :Channel topic", to);


    /*
     * :ergo.test 353 ukiomobilenick = #1 :@nick ukiomobilenick
     * :ft_irc.42 353 nick = #2 :@qwe nick
     */
    Message RPL_NAMREPLY(":" + serverName + " 353 " + to->getNick() + " = #" + channelName + " :" + names, to);


    /*
     *
     * :ft_irc.42 366 nick #2 :End of NAMES list
     * :ergo.test 366 ukiomobilenick #1 :End of NAMES list
     */
    Message RPL_ENDOFNAMES(":" + serverName + " 366 " + to->getNick() + " #" + channelName + " :End of NAMES list", to);

    result.push_back(RPL_NAMTOPIC);
    result.push_back(RPL_NAMREPLY);
    result.push_back(RPL_ENDOFNAMES);

    return result;
}

/**
 * Try to append new user. If it fails - return Message with error.
 * If no Message returned - User append was successful
 * @param newUser
 * @return
 */
ft::optional<Message> IRCChannel::appendUser(User::Ptr newUser) {
    if (std::find(users.begin(), users.end(), newUser) != users.end()) {
        //TODO: Error - user already joined in the channel
    }
    users.push_back(newUser);
    return ft::nullopt;
}

