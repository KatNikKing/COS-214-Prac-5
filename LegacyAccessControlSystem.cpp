#include "LegacyAccessControlSystem.h"

LegacyAccessControlSystem::LegacyAccessControlSystem(CampusComponent* campus) : campus(campus) {}

void LegacyAccessControlSystem::activateLock(int unitCode) {
    if (campus != nullptr) {
        CampusComponent* unit = campus->get(unitCode);
        if (unit != nullptr) {
            unit->restrictAccess();
            cout << "Access to Campus Component '" << unit->getName() 
                 << "' (Code: " << to_string(unitCode) << ") has been restricted.\n";
        }
    }
}

void LegacyAccessControlSystem::deactivateLock(int unitCode) {
    if (campus != nullptr) {
        CampusComponent* unit = campus->get(unitCode);
        if (unit != nullptr) {
            unit->restoreAccess();
            cout << "Access to Campus Component '" << unit->getName() 
                 << "' (Code: " << to_string(unitCode) << ") has been restricted.\n";
        }
    }
}