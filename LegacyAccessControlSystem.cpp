#include "LegacyAccessControlSystem.h"

LegacyAccessControlSystem::LegacyAccessControlSystem(CampusComponent* campus) : campus(campus) {}

void LegacyAccessControlSystem::activateLock(int unitCode) {
    if (campus != nullptr) {
        CampusComponent* unit = campus->get(unitCode);
        if (unit != nullptr) {
            unit->restrictAccess();
        }
    }
}

void LegacyAccessControlSystem::deactivateLock(int unitCode) {
    if (campus != nullptr) {
        CampusComponent* unit = campus->get(unitCode);
        if (unit != nullptr) {
            unit->restoreAccess();
        }
    }
}