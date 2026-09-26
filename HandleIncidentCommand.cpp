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

    Report report(incident->getLocation(), incident,
                  "Incident #" + std::to_string(incident->getId()) + " reported",
                  ReportType::INCIDENT_REPORTED, false);
    coordinator->notify(report);
    executed = true;
}

void HandleIncidentCommand::undo() {
    if (!executed) {
        return;
    }

    incident->cancel();

    Report report(incident->getLocation(), incident,
                  "Incident #" + std::to_string(incident->getId()) + " withdrawn",
                  ReportType::INCIDENT_REPORT_WITHDRAWN, false);
    coordinator->notify(report);
    executed = false;
}

std::string HandleIncidentCommand::describe() const {
    return "Handle incident #" + std::to_string(incident->getId());
}