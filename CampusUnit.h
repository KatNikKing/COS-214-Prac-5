#ifndef CAMPUS_UNIT
#define CAMPUS_UNIT

#include "CampusComponent.h"

class CampusUnit : public CampusComponent {
    public:
        CampusUnit(string name);
        CampusComponent* get(int code) override;
        void restrictAccess() override;
        void restoreAccess() override;
};

#endif