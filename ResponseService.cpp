#include "ResponseService.h"
#include "ResponseUnit.h"

ResponseService::~ResponseService() {
    for (ResponseUnit* unit : units)
        delete unit;
}

ResponseUnit* ResponseService::dispatchUnit(Incident* incident, CampusComponent* location) {
    if (location == nullptr)
        location = incident->getLocation();

    for (ResponseUnit* unit : units) {
        if (dynamic_cast<Available*>(unit->getStatus()) != nullptr) {
            unit->dispatch(incident, location);
            cout << "Response Unit successfully dispatched.\n";
            return unit;
        }
    }

    cout << "Response Unit dispatch failed: no available Response Units.\n";
    return nullptr;
}

void ResponseService::recallUnit(string name) {
    for (ResponseUnit* unit : units) {
        if (unit->getName() == name)
            unit->recall();
    }
}

void ResponseService::addUnit(ResponseUnit* unit) {
    if (unit != nullptr) {
        bool exists = false;
        for (ResponseUnit* u : units) {
            if (u == unit) {
                exists = true;
                break;
            }
        }

        if (!exists)
            units.push_back(unit);
    }
}

void ResponseService::removeUnit(string name) {
    for (vector<ResponseUnit*>::iterator it = units.begin(); it != units.end(); it++) {
        if ((*it)->getName() == name) {
            units.erase(it);
            break;
        }
    } 
}

vector<ResponseUnit*> ResponseService::getDispatchedUnits(Incident* incident) {
    vector<ResponseUnit*> dispatchedUnits;
    for (ResponseUnit* unit : units) {
        if (unit->getIncident() == incident) 
            dispatchedUnits.push_back(unit);
    }
    return dispatchedUnits;
}