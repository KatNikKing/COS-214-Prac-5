#include "CampusComponent.h"

int CampusComponent::codeCount = 0;
CampusComponent::CampusComponent(string name) : name(name), code(++codeCount), accessRestricted(false)  {}

void CampusComponent::add(CampusComponent* component) {}

void CampusComponent::remove(int code) {}

string CampusComponent::getName() {
    return name;
}

bool CampusComponent::accessIsRestricted() {
    return accessRestricted;
}

int CampusComponent::getCode() {
    return code;
}