#include "DispatchUnitCommand.h"
#include "ResponseService.h"
#include "ResponseUnit.h"
#include "Incident.h"
#include "CampusComponent.h"

DispatchUnitCommand::DispatchUnitCommand(ResponseService* service, Incident* incident, CampusComponent* location)
    : service(service), incident(incident), location(location), unit(nullptr) {}

DispatchUnitCommand::~DispatchUnitCommand() {}

void DispatchUnitCommand::execute() {
    unit = service->dispatchUnit(incident, location);
}

void DispatchUnitCommand::undo() {
    if (unit == nullptr) {
        return;
    }
    service->recallUnit(unit->getName());
    unit = nullptr;
}

std::string DispatchUnitCommand::describe() const {
    std::string text = "Dispatch unit to " + location->getName() +
                       " (incident #" + std::to_string(incident->getId()) + ")";
    if (unit != nullptr) {
        text += " [" + unit->getName() + "]";
    }
    return text;
}