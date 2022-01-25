#ifndef COMMANDSHANDLER_HPP
#define COMMANDSHANDLER_HPP

class CommandsHandler {
public:
    CommandsHandler();

    ~CommandsHandler();

    void handleCommands();

    void execCommand(std::deque<ClientMessage::Ptr>::iterator cmd_it);
};


#endif
