#include "EmergencyDesk.h"
#include <iostream>

EmergencyDesk::EmergencyDesk(Coordinator* coordinator, OperatorConsole* console, ResponseService* security, ResponseService* medical,
                             ResponseService* facilities, AccessControlService* access, AlertService* alerts)
    : coordinator(coordinator), console(console), security(security), medical(medical), 
      facilities(facilities), access(access), alerts(alerts) {}

EmergencyDesk::~EmergencyDesk() {}

int EmergencyDesk::respondToFire(Incident* incident, CampusComponent* area) {
    std::cout << "\n[EmergencyDesk] Fire response at " << area->getName() << "\n";
    int steps = 0;

    if (console->submit(new HandleIncidentCommand(coordinator, incident))) {
        ++steps;
    }

    if (console->submit(new DispatchUnitCommand(security, incident, area))) {
        ++steps;
    }

    if (console->submit(new DispatchUnitCommand(facilities, incident, area))) {
        ++steps;
    }

    if (console->submit(new RestrictAccessCommand(access, area))) {
        ++steps;
    }

    if (console->submit(new SendAlertCommand(alerts, "Fire at " + area->getName() + " - avoid the area"))) {
        ++steps;
    }

    std::cout << "[EmergencyDesk] Fire response complete: " << steps << "/5 steps succeeded\n";
    return steps;
}

int EmergencyDesk::respondToMedical(Incident* incident, CampusComponent* area, bool alertCampus) {
    std::cout << "\n[EmergencyDesk] Medical response at " << area->getName() << "\n";
    int steps = 0;

    if (console->submit(new HandleIncidentCommand(coordinator, incident))) {
        ++steps;
    }

    if (console->submit(new DispatchUnitCommand(medical, incident, area))) {
        ++steps;
    }

    if (alertCampus) {
        if (console->submit(new SendAlertCommand(alerts, "Medical emergency at " + area->getName()))) {
            ++steps;
        }
    }

    std::cout << "[EmergencyDesk] Medical response complete: " << steps << " step(s) succeeded\n";
    return steps;
}

void EmergencyDesk::standDown(int steps) {
    std::cout << "[EmergencyDesk] Standing down last " << steps << " action(s)\n";
    for (int i = 0; i < steps; ++i) {
        if (!console->undoLast()) {
            std::cout << "[EmergencyDesk] Stand-down stopped early - nothing left to undo\n";
            break;
        }
    }
}