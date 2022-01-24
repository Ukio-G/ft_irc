//
// Created by ukio on 1/24/22.
//

#include <src/ApplicationData.hpp>
#include "CommandsHandler.hpp"

CommandsHandler::CommandsHandler() : m_cap_lock(false) {}

CommandsHandler::~CommandsHandler() {
}

void CommandsHandler::popCommand() {
    ApplicationData::Ptr app_data = ApplicationData::instance();

    Command::Ptr cmd = app_data->commandQueue.front();
    app_data->commandQueue.pop_front();

    std::vector<MessageBNF> cmd_result = cmd->exec();
    for (int i = 0; i < cmd_result.size(); ++i)
        app_data->server->WriteStr(cmd_result[i], cmd->getMSockSource());

}

void CommandsHandler::handleCommands() {
    ApplicationData::Ptr app_data = ApplicationData::instance();
    while (!m_cap_lock) {
        popCommand();
        if (app_data->commandQueue.empty())
            return;
    }
}

void CommandsHandler::capUnlock() {
    m_cap_lock = false;
}

