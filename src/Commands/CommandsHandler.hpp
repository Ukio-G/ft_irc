#ifndef COMMANDSHANDLER_HPP
#define COMMANDSHANDLER_HPP

class CommandsHandler {
public:
    CommandsHandler();

    ~CommandsHandler();

    void popCommand();
private:
    bool m_cap_lock;
public:
    void capUnlock();

    void handleCommands();
};


#endif
