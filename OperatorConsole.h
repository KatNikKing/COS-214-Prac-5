#ifndef OPERATOR_CONSOLE_H
#define OPERATOR_CONSOLE_H

#include <vector>
#include "Command.h"

class OperatorConsole {
    public:
        OperatorConsole();
        ~OperatorConsole();
        bool submit(Command* cmd);
        bool undoLast();
        int historySize() const;
        void printHistory() const;

    private:
        std::vector<Command*> history;
};

#endif // OPERATOR_CONSOLE_H