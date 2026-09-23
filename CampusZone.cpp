#include "CampusZone.h"

CampusZone::CampusZone(string name) : CampusComponent(name) {}

CampusZone::~CampusZone() {
    for (CampusComponent* component : components)
        delete component;
}

void CampusZone::add(CampusComponent* component) {
    if (component != nullptr) {
        bool exists = false;
        for (CampusComponent* c : components) {
            if (c == component) {
                exists = true;
                break;
            }
        }

        if (!exists)
            components.push_back(component);
    }   
}

void CampusZone::remove(int code) {
    for (vector<CampusComponent*>::iterator it = components.begin(); it != components.end(); it++) {
        if ((*it)->getCode() == code) {
            delete *it;
            components.erase(it);
            return;
        }
    }

    for (CampusComponent* component : components)
        component->remove(code);
}

CampusComponent* CampusZone::get(int code) {
    for (CampusComponent* component : components) {
        if (component->getCode() == code) 
            return component;
    }
    for (CampusComponent* component : components) {
        CampusComponent* c = component->get(code);
        if (c != nullptr) 
            return c;
    }
    return nullptr;
}

void CampusZone::restrictAccess() {
    accessRestricted = true;
    for (CampusComponent* component : components)
        component->restrictAccess();
}

void CampusZone::restoreAccess() {
    accessRestricted = false;
    for (CampusComponent* component : components)
        component->restoreAccess();
}