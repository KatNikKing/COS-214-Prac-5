#ifndef ACCESS_CONTROL_ADAPTER
#define ACCESS_CONTROL_ADAPTER

#include "AccessControlService.h"
#include "LegacyAccessControlSystem.h"

class AccessControlAdapter : public AccessControlService {
    private:
        LegacyAccessControlSystem* legacyAccessControl;
    public:
        AccessControlAdapter(LegacyAccessControlSystem* legacyAccessControl);
        void restrictAccess(CampusComponent* area) override;
        void restoreAccess(CampusComponent* area) override;
};

#endif