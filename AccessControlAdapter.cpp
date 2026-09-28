#include "AccessControlAdapter.h"

AccessControlAdapter::AccessControlAdapter(LegacyAccessControlSystem* legacyAccessControl) 
                    : legacyAccessControl(legacyAccessControl) {}

void AccessControlAdapter::restrictAccess(CampusComponent* area) {
    if (area != nullptr)
        legacyAccessControl->activateLock(area->getCode());
}

void AccessControlAdapter::restoreAccess(CampusComponent* area) {
    if (area != nullptr)
        legacyAccessControl->deactivateLock(area->getCode());
}