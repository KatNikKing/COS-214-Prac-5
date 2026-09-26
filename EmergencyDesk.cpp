#include "EmergencyDesk.h"
#include "CampusCoordinator.h"
#include "RestrictAccessCommand.h"
#include "OperatorConsole.h"
#include "DispatchUnitCommand.h"
#include "SendAlertCommand.h"
#include "HandleIncidentCommand.h"
#include "ResponseUnit.h"

EmergencyDesk::EmergencyDesk(Coordinator* coordinator)
    : coordinator(coordinator != nullptr ? coordinator : new CampusCoordinator), console(new OperatorConsole), 
      security(nullptr), medical(nullptr), facilities(nullptr), access(nullptr), alerts(nullptr), currentIncident(nullptr) {
      coordinator->removeAllServices();
}

EmergencyDesk::~EmergencyDesk() {
    delete console;
}

int EmergencyDesk::handleIncident(Incident* incident) {
    if (incident->getStatus() != "reported") return;
    cout << "==========NEW INCIDENT REPORTED==========\n"
         << "[EmergencyDesk] Location: " << incident->getLocation()->getName() << endl
         << "[EmergencyDesk] Description:\n" << incident->getDescription() << endl << endl;

    cout << "[EmergencyDesk] Coordinating services...\n";
    if (!console->submit(new HandleIncidentCommand(coordinator, incident))) {
        cout << "[EmergencyDesk] Failed to handle incident.\n";
        cout << "=========================================\n";
        return 1;
    }
    cout << endl;

    cout << "[EmergencyDesk] Reporting on dispatched units...\n";
    vector<ResponseUnit*> dispatchedUnits;
    if (security != nullptr) {
        for (ResponseUnit* unit : security->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    if (medical != nullptr) {
        for (ResponseUnit* unit : medical->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    if (facilities != nullptr) {
        for (ResponseUnit* unit : facilities->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->performDuty();
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->setStatus(new Operating);
        unit->performDuty();
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->recall();
        unit->performDuty();
    }
    cout << endl;

    incident->resolve();
    cout << "=========================================\n";
    return 1;
}

int EmergencyDesk::respondToFire(Incident* incident) {
    if (incident->getStatus() != "reported") return;
    cout << "==========FIRE EMERGENCY REPORTED==========\n"
         << "[EmergencyDesk] Location: " << incident->getLocation()->getName() << endl
         << "[EmergencyDesk] Description:\n" << incident->getDescription() << endl << endl;
    
    int steps = 0;

    incident->activate();

    if (console->submit(new DispatchUnitCommand(security, incident, incident->getLocation()))) {
        ++steps;
    }

    if (console->submit(new DispatchUnitCommand(medical, incident, incident->getLocation()))) {
        ++steps;
    }

    if (console->submit(new DispatchUnitCommand(facilities, incident, incident->getLocation()))) {
        ++steps;
    }

    if (console->submit(new RestrictAccessCommand(access, incident->getLocation()))) {
        ++steps;
    }

    if (console->submit(new SendAlertCommand(alerts, "Fire at " + incident->getLocation()->getName() + " - avoid the area"))) {
        ++steps;
    }

    cout << "\n[EmergencyDesk] Reporting on dispatched units...\n";
    vector<ResponseUnit*> dispatchedUnits;
    if (security != nullptr) {
        for (ResponseUnit* unit : security->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    if (medical != nullptr) {
        for (ResponseUnit* unit : medical->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    if (facilities != nullptr) {
        for (ResponseUnit* unit : facilities->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->performDuty();
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->setStatus(new Operating);
        unit->performDuty();
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->recall();
        unit->performDuty();
    }
    incident->resolve();
    cout << endl;

    std::cout << "[EmergencyDesk] Fire response complete: " << steps << "/5 steps succeeded\n";
    cout << "=========================================\n";
    
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

bool EmergencyDesk::manageIncident(Incident* incident) {
    if (incident->getStatus() != "reported") {
        cout << "[EmergencyDesk] Incident cannot be managed.\n";
        return false;
    }
    if (currentIncident == nullptr) {
        cout << "[EmergencyDesk] Resolve current incident first.\n";
        return false;
    }
    
    currentIncident = incident;
    cout << "[EmergencyDesk] New incident being managed...\n"
         << "[EmergencyDesk] Location: " << incident->getLocation()->getName() << endl
         << "[EmergencyDesk] Description:\n" << incident->getDescription() << endl << endl;

    cout << "[EmergencyDesk] Coordinating services...\n";
    if (!console->submit(new HandleIncidentCommand(coordinator, incident))) {
        cout << "[EmergencyDesk] Failed to handle incident.\n";
        return false;
    }
    cout << endl;
    
    cout << "[EmergencyDesk] Reporting on dispatched units...\n";
    if (security != nullptr) {
        for (ResponseUnit* unit : security->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    if (medical != nullptr) {
        for (ResponseUnit* unit : medical->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    if (facilities != nullptr) {
        for (ResponseUnit* unit : facilities->getDispatchedUnits(incident))
            dispatchedUnits.push_back(unit);
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->performDuty();
    }
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->setStatus(new Operating);
        unit->performDuty();
    }
    
    return true;
}

vector<ResponseUnit*> EmergencyDesk::getDispatchedUnits() {
    return dispatchedUnits;
}

void EmergencyDesk::resolveIncident() {
    cout << "[EmergencyDesk] Resolving current incident...\n";
    for (ResponseUnit* unit : dispatchedUnits) {
        unit->recall();
    }
    currentIncident->resolve();
    currentIncident = nullptr;
    dispatchedUnits.clear();
}

bool EmergencyDesk::registerService(SecurityService* service) {
    if (security != nullptr || service == nullptr) 
        return false;
    security = service;
    coordinator->addService(security);
    return true;
}

bool EmergencyDesk::registerService(MedicalService* service) {
    if (medical != nullptr || service == nullptr) 
        return false;
    medical = service;
    coordinator->addService(medical);
    return true;
}

bool EmergencyDesk::registerService(FacilitiesService* service) {
    if (facilities != nullptr || service == nullptr) 
        return false;
    facilities = service;
    coordinator->addService(facilities);
    return true;
}

bool EmergencyDesk::registerService(AccessControlService* service) {
    if (access != nullptr || service == nullptr) 
        return false;
    access = service;
    coordinator->addService(access);
    return true;
}

bool EmergencyDesk::registerService(AlertService* service) {
    if (alerts != nullptr || service == nullptr) 
        return false;
    alerts = service;
    coordinator->addService(alerts);
    return true;
}