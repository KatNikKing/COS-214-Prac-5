#include "CampusUnit.h"

CampusUnit::CampusUnit(string name) : CampusComponent(name) {}

CampusComponent* CampusUnit::get(int code) {
    if (this->getCode() == code)
        return this;
    return nullptr;
}

void CampusUnit::restrictAccess() {
    accessRestricted = true;
}

void CampusUnit::restoreAccess() {
    accessRestricted = false;
}