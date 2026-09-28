#ifndef ACCESS_CONTROL_SERVICE
#define ACCESS_CONTROL_SERVICE

#include "Service.h"

class AccessControlService : public Service {
    public:
        virtual ~AccessControlService() = default;
        virtual void receiveReport(Report report) override;
        virtual void restrictAccess(CampusComponent* area);
        virtual void restoreAccess(CampusComponent* area);
};

#endif