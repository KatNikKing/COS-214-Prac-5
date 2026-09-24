#ifndef HANDLE_INCIDENT_COMMAND_H
#define HANDLE_INCIDENT_COMMAND_H

#include <string>
#include "Command.h"

class Coordinator;
class Incident;

class HandleIncidentCommand : public Command {
    public:
        HandleIncidentCommand(Coordinator* coordinator, Incident* incident);
        ~HandleIncidentCommand() override;
        void execute() override;
        void undo() override;
        std::string describe() const override;

    private:
        Coordinator* coordinator;
        Incident* incident;
        bool executed;
};

#endif // HANDLE_INCIDENT_COMMAND_H