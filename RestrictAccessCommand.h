#ifndef RESTRICT_ACCESS_COMMAND_H
#define RESTRICT_ACCESS_COMMAND_H

#include <string>
#include "Command.h"

class AccessControlService;
class CampusComponent;

class RestrictAccessCommand : public Command {
    public:
        RestrictAccessCommand(AccessControlService* access, CampusComponent* area);
        ~RestrictAccessCommand() override;
        void execute() override;
        void undo() override;
        std::string describe() const override;

    private:
        AccessControlService* access;
        CampusComponent* area;
        bool wasRestricted;
};

#endif // RESTRICT_ACCESS_COMMAND_H