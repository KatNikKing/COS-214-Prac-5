#include "ResponseUnit.h"

ResponseUnit::ResponseUnit(string name, ResponseService* service) 
            : name(name), status(new Available), incident(nullptr), location(nullptr), service(service) {}

ResponseUnit::~ResponseUnit() {
    delete status;
}

void ResponseUnit::dispatch(Incident* incident, CampusComponent* location) {
    if (incident != nullptr && location != nullptr) {
        this->incident = incident;
        this->location = location;
        setStatus(new Dispatched(location->getName()));
    }
}

void ResponseUnit::recall() {
    setStatus(new Available);
}

void ResponseUnit::performDuty() {
    cout << "Response Unit '" << name << "' ";
    status->performDuty();
}

void ResponseUnit::report(Report report) {
    service->report(report);
}

string ResponseUnit::getName() {
    return name;
}

void ResponseUnit::setStatus(UnitStatus* status) {
    if (status != nullptr) {
        delete this->status;
        this->status = status;
    }
}

UnitStatus* ResponseUnit::getStatus() {
    return status;
}

Incident* ResponseUnit::getIncident() {
    return incident;
}

CampusComponent* ResponseUnit::getLocation() {
    return location;
}

ResponseService* ResponseUnit::getService() {
    return service;
}