#include "OperatorConsole.h"
#include <iostream>
#include <exception>

OperatorConsole::OperatorConsole() {}

OperatorConsole::~OperatorConsole() {
    for (unsigned int i = 0; i < history.size(); ++i) {
        delete history[i];
    }
    history.clear();
}

bool OperatorConsole::submit(Command* cmd) {
    if (cmd == nullptr) {
        std::cout << "[Console] FAILED: null command\n";
        return false;
    }

    try {
        cmd->execute();
    } catch (const std::exception& e) {
        std::cout << "[Console] FAILED: " << cmd->describe() << " - " << e.what() << "\n";
        delete cmd;
        return false;
    }

    std::cout << "[Console] OK: " << cmd->describe() << "\n";
    history.push_back(cmd);
    return true;
}

bool OperatorConsole::undoLast() {
    if (history.empty()) {
        std::cout << "[Console] Nothing to undo\n";
        return false;
    }

    Command* last = history.back();

    try {
        last->undo();
    } catch (const std::exception& e) {
        std::cout << "[Console] UNDO FAILED: " << last->describe() << " - " << e.what() << "\n";
        return false;
    }

    std::cout << "[Console] UNDO: " << last->describe() << "\n";
    history.pop_back();
    delete last;
    return true;
}

int OperatorConsole::historySize() const {
    return static_cast<int>(history.size());
}

void OperatorConsole::printHistory() const {
    std::cout << "--- Command history (" << history.size() << ") ---\n";
    for (unsigned int i = 0; i < history.size(); ++i) {
        std::cout << (i + 1) << ". " << history[i]->describe() << "\n";
    }
}