#include "Incident.h"

#include <string>
#include <vector>
#include <algorithm>

Incident::Incident(int id, CampusComponent* location, string description, IncidentStatus* status) : id(id), location(location), description(description), status(status){

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

string Incident::getDescription() {
    return description;
}

void Incident::addReport(Report r){
    reports.emplace_back(r);
}

void Incident::removeReport(Report r){
    auto it = std::find(reports.begin(), reports.end(), r);
    if (it != reports.end()) {
        reports.erase(it); 
    }
}
