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
        Message msg = Message(str, users[i], from);
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

    Message RPL_NAMTOPIC("332 " + to->getNick() + " #" + channelName + " :Channel topic", to);
    Message RPL_NAMREPLY("353 " + to->getNick() + " = #" + channelName + " :" + names, to);
    Message RPL_ENDOFNAMES("366 " + to->getNick() + " #" + channelName + " :End of NAMES list", to);

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
        return ft::nullopt;
    }
    users.push_back(newUser);
    return ft::nullopt;
}

/**
 * Try to append new user. If it fails - return Message with error.
 * If no Message returned - User append was successful
 * @param newUser
 * @return
 */
ft::optional<Message> IRCChannel::appendUserAsOperator(User::Ptr newUser) {
    if (!isUserAvailable(newUser))
        return ft::nullopt;         //TODO: Error - try to make operator user, which not on the channel

    if (isChannelOperator(newUser)) {
        //TODO: Error - user already operator
        return ft::nullopt;
    }
    operators.push_back(newUser);
    return ft::nullopt;
}

bool IRCChannel::isUserAvailable(User::Ptr user) {
    std::vector<User::Ptr>::iterator uIt = std::find(users.begin(), users.end(), user);
    return uIt != users.end();
}

void IRCChannel::removeUser(User::Ptr user) {
    std::vector<User::Ptr>::iterator uIt = std::find(users.begin(), users.end(), user);
    if (uIt != users.end()) users.erase(uIt);

    uIt = std::find(operators.begin(), operators.end(), user);
    if (uIt != users.end()) users.erase(uIt);
}

bool IRCChannel::isChannelOperator(User::Ptr user) {
    if (!isUserAvailable(user))
        return false;
    std::vector<User::Ptr>::iterator uIt = std::find(operators.begin(), operators.end(), user);

    return uIt != operators.end();
}

