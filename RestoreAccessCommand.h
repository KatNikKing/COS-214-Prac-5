#ifndef RESTORE_ACCESS_COMMAND_H
#define RESTORE_ACCESS_COMMAND_H

#include <string>
#include "Command.h"

class AccessControlService;
class CampusComponent;

class RestoreAccessCommand : public Command {
    public:
        RestoreAccessCommand(AccessControlService* access, CampusComponent* area);
        ~RestoreAccessCommand() override;
        void execute() override;
        void undo() override;
        std::string describe() const override;

    private:
        AccessControlService* access;
        CampusComponent* area;
        bool wasRestricted;
};

#endif // RESTORE_ACCESS_COMMAND_H