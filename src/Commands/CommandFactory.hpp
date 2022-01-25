//
// Created by ukio on 1/24/22.
//

#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP


#include "ClientMessage.hpp"

class CommandFactory {
public:
    CommandFactory();

    CommandFactory(const CommandFactory &other);

    ~CommandFactory();

    ClientMessage::Ptr createCommand(const Message &msg);
};


#endif
