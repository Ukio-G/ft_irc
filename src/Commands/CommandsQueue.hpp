#ifndef COMMANDSQUEUE_HPP
#define COMMANDSQUEUE_HPP

class CommandsQueue {
public:
    CommandsQueue();

    ~CommandsQueue();

    void handleCommands();

    void execCommand(std::deque<ClientMessage::Ptr>::iterator cmd_it);
};


#endif
