#ifndef LEGACY_ACCESS_CONTROL_SYSTEM
#define LEGACY_ACCESS_CONTROL_SYSTEM

#include "Service.h"

class LegacyAccessControlSystem {
    private:
        CampusComponent* campus;
    
    public:
        LegacyAccessControlSystem(CampusComponent* campus);
        virtual ~LegacyAccessControlSystem() = default;
        void activateLock(int unitCode);
        void deactivateLock(int unitCode);
        
};

#endif