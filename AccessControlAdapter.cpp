#include "AccessControlAdapter.h"

void AccessControlAdapter::restrictAccess(CampusComponent* area) {
    if (area != nullptr)
        activateLock(area->getCode());
}

void AccessControlAdapter::restoreAccess(CampusComponent* area) {
    if (area != nullptr)
        deactivateLock(area->getCode());
}