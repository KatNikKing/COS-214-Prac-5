#ifndef ACCESS_CONTROL_ADAPTER
#define ACCESS_CONTROL_ADAPTER

#include "AccessControlService.h"
#include "LegacyAccessControlSystem.h"

class AccessControlAdapter : public AccessControlService, private LegacyAccessControlSystem {
    public:
        AccessControlAdapter(CampusComponent* campus);
        void restrictAccess(CampusComponent* area) override;
        void restoreAccess(CampusComponent* area) override;
};

#endif