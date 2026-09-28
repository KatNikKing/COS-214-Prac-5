#ifndef DISPATCH_UNIT_COMMAND_H
#define DISPATCH_UNIT_COMMAND_H

#include <string>
#include "Command.h"

class ResponseService;
class ResponseUnit;
class Incident;
class CampusComponent;

class DispatchUnitCommand : public Command {
    public:
        DispatchUnitCommand(ResponseService* service, Incident* incident, CampusComponent* location);
        ~DispatchUnitCommand() override;
        void execute() override;
        void undo() override;
        std::string describe() const override;

    private:
        ResponseService* service;
        Incident* incident;
        CampusComponent* location;
        ResponseUnit* unit;
};

#endif // DISPATCH_UNIT_COMMAND_H