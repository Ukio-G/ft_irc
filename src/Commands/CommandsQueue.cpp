//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "CommandsQueue.hpp"

CommandsQueue::CommandsQueue() { }

CommandsQueue::~CommandsQueue() { }


/**
 * Exec one command from client. Can produse zero, one, or multiply server responses
 * @param cmd_it
 */
void CommandsQueue::execCommand(std::deque<ClientMessage::Ptr>::iterator cmd_it) {
    ApplicationData::Ptr app_data = ApplicationData::instance();

    ft::optional<ServerResponse> cmd_result = (*cmd_it)->exec();

    if (cmd_result)
        app_data->server->Write(cmd_result.value());
}

void CommandsQueue::handleCommands() {
    ApplicationData::Ptr app_data = ApplicationData::instance();

    typedef std::deque<ClientMessage::Ptr>::iterator cmdIt;

    for (cmdIt it = app_data->commandQueue.begin() ; it != app_data->commandQueue.end(); ) {
        const Message & msg = it->get()->m_message;
        int from = msg.m_from;
        if (app_data->lockedCap.find(from) != app_data->lockedCap.end()) {
            if (msg.messageBnf.command != "CAP") {
                it++;
                continue;
            }
        }
        execCommand(it);
        it = app_data->commandQueue.erase(it);
    }

}

