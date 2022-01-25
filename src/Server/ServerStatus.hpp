//
// Created by ukio on 1/25/22.
//

#ifndef SERVERSTATUS_HPP
#define SERVERSTATUS_HPP


#include <src/Message/Message.hpp>

class ServerStatus {
public:

    enum Reply {
        RPL_LUSERCLIENT = 251,
        RPL_LUSEROP = 252,
        RPL_LUSERUNKNOWN = 253,
        RPL_LUSERCHANNELS = 254,
        RPL_LUSERME = 255
    };

    ServerStatus();

    ServerStatus(const ServerStatus &other);

    ServerStatus &operator=(const ServerStatus &other);

    ~ServerStatus();

    Message getReplyMessage(Reply reply, User::Ptr to);

private:
    Message rpl_luserclient(User::Ptr to);
    Message rpl_luserop(User::Ptr to);
    Message rpl_luserunknown(User::Ptr to);
    Message rpl_luserchannels(User::Ptr to);
    Message rpl_luserme(User::Ptr to);
};


#endif
