#include "HandleIncidentCommand.h"
#include "Coordinator.h"
#include "Incident.h"
#include "CampusComponent.h"
#include "Report.h"

HandleIncidentCommand::HandleIncidentCommand(Coordinator* coordinator, Incident* incident)
    : coordinator(coordinator), incident(incident), executed(false) {}

HandleIncidentCommand::~HandleIncidentCommand() {}

void HandleIncidentCommand::execute() {
    incident->activate();
    coordinator->notify(Report(incident, incident->getLocation(), ReportType::INCIDENT_REPORTED));
    executed = true;
}

void HandleIncidentCommand::undo() {
    if (!executed) {
        return;
    }

    incident->cancel();
    coordinator->notify(Report(incident, incident->getLocation(), ReportType::INCIDENT_REPORT_WITHDRAWN));
    executed = false;
}

std::string HandleIncidentCommand::describe() const {
    return "Handle incident #" + std::to_string(incident->getId());
}