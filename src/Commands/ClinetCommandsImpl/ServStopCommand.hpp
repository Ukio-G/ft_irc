//
// Created by ukio on 1/24/22.
//

#ifndef SERVSTOPCOMMAND_HPP
#define SERVSTOPCOMMAND_HPP

#include "src/Commands/ClientMessage.hpp"

class ServStopCommand : public ClientMessage {
public:
    ServStopCommand();

    ServStopCommand(const ServStopCommand &other);

    ServStopCommand(const Message &message);

    ServStopCommand &operator=(const ServStopCommand &other);

    ~ServStopCommand();

private:
    ft::optional<ServerResponse> exec();
};


#endif
