#include "ResponseUnit.h"

ResponseUnit::ResponseUnit(string name, ResponseService* service) 
            : name(name), status(new Available), incident(nullptr), location(nullptr), service(service) {}

ResponseUnit::~ResponseUnit() {
    delete status;
}

void ResponseUnit::dispatch(Incident* incident, CampusComponent* location) {
    if (incident != nullptr && location != nullptr && dynamic_cast<Available*>(status) != nullptr) {
        this->incident = incident;
        this->location = location;
        setStatus(new Dispatched(location->getName()));
        performDuty();
    }
}

void ResponseUnit::operate() {
    if (dynamic_cast<Dispatched*>(status) != nullptr) {
        setStatus(new Operating);
        performDuty(); 
    }
}

void ResponseUnit::recall(bool avail) {
    if (dynamic_cast<Operating*>(status) != nullptr || dynamic_cast<Unavailable*>(status) != nullptr) {
        incident = nullptr;
        if (avail)
            setStatus(new Available);
        else   
            setStatus(new Unavailable);
        performDuty();
    }       
}

void ResponseUnit::performDuty() {
    cout << service->toString() << " Response Unit '" << name << "' ";
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