//
// Created by ukio on 1/29/22.
//

#ifndef NOTICECOMMAND_HPP
#define NOTICECOMMAND_HPP


#include <src/Commands/ClientMessage.hpp>

class NoticeCommand : public ClientMessage {
public:
    NoticeCommand();

    NoticeCommand(const NoticeCommand &other);

    NoticeCommand(const Message &message);

    NoticeCommand &operator=(const NoticeCommand &other);

    ~NoticeCommand();

    virtual ft::optional<ServerResponse> exec();

private:
};


#endif
