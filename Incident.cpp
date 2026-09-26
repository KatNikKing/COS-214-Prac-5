#include "Incident.h"

#include <string>

Incident::Incident(int id, CampusComponent* location, string description, int severity, IncidentStatus* status) : id(id), location(location), description(description), severity(severity), status(status){

}

Incident::~Incident(){
    delete status; 
}

void Incident::activate(){
    status->activate(this);
}

void Incident::resolve(){
    status->resolve(this);
}

void Incident::cancel(){
    status->cancel(this);
}

void Incident::setStatus(IncidentStatus* status){
    if (status != nullptr) {
        delete this->status;
        this->status = status;
    }
}

string Incident::getStatus(){
    return status->getName();
}

CampusComponent* Incident::getLocation(){
    return location;
}
int Incident::getId(){
    return id;
}