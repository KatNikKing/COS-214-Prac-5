#include "IncidentStatus.h"
#include "Incident.h"
#include <iostream>

// NOTE: this file assumes Incident exposes:
//     void setStatus(IncidentStatus* status);
// which should behave exactly like ResponseUnit::setStatus(UnitStatus*) does -
// delete the old state object, then take ownership of the new one.

void Reported::activate(Incident* incident) {
    cout << "Incident is now active\n";
    incident->setStatus(new Active);
}

void Reported::resolve(Incident* incident) {
    cout << "Cannot resolve an incident that has not been activated yet\n";
}

void Reported::cancel(Incident* incident) {
    cout << "Incident is now cancelled\n";
    incident->setStatus(new Cancelled);
}

void Active::activate(Incident* incident) {
    cout << "Incident is already active\n";
}

void Active::resolve(Incident* incident) {
    cout << "Incident is now resolved\n";
    incident->setStatus(new Resolved);
}

void Active::cancel(Incident* incident) {
    cout << "Incident is now cancelled after being active\n";
    incident->setStatus(new Cancelled);
}

void Resolved::activate(Incident* incident) {
    cout << "Cannot reactivate a resolved incident\n";
}

void Resolved::resolve(Incident* incident) {
    cout << "Incident is already resolved\n";
}

void Resolved::cancel(Incident* incident) {
    cout << "Cannot cancel an incident that has already been resolved\n";
}

void Cancelled::activate(Incident* incident) {
    cout << "Cannot reactivate a cancelled incident\n";
}

void Cancelled::resolve(Incident* incident) {
    cout << "Cannot resolve a cancelled incident\n";
}

void Cancelled::cancel(Incident* incident) {
    cout << "Incident is already cancelled\n";
}