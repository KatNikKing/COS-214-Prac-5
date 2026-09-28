#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
    public:
        virtual ~Command() = default;
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual std::string describe() const = 0;

    protected:
        Command() = default;
};

#endif // COMMAND_H