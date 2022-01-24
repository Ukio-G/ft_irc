//
// Created by ukio on 1/24/22.
//

#ifndef COMMANDFACTORY_HPP
#define COMMANDFACTORY_HPP


#include "Command.hpp"

class CommandFactory {
public:
    CommandFactory();

    CommandFactory(const CommandFactory &other);

    ~CommandFactory();

    Command::Ptr createCommand(const std::pair<std::string, int> &clientMessage);

private:

};


#endif
