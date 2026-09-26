#include "AccessControlAdapter.h"

AccessControlAdapter::AccessControlAdapter(CampusComponent* campus) : LegacyAccessControlSystem(campus) {}

void AccessControlAdapter::restrictAccess(CampusComponent* area) {
    if (area != nullptr)
        activateLock(area->getCode());
}

void AccessControlAdapter::restoreAccess(CampusComponent* area) {
    if (area != nullptr)
        deactivateLock(area->getCode());
}