//
// Created by ukio on 1/26/22.
//

#ifndef MODECOMMAND_HPP
#define MODECOMMAND_HPP


#include <src/Server/ServerResponse.hpp>
#include <optional.hpp>
#include <src/Commands/ClientMessage.hpp>

class ModeCommand : public ClientMessage {
public:
    ModeCommand();

    ModeCommand(const ModeCommand &other);

    ModeCommand(const Message &message);

    ModeCommand &operator=(const ModeCommand &other);

    ~ModeCommand();

    ft::optional<ServerResponse> exec();

private:
};


#endif
