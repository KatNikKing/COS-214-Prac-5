#ifndef CAMPUS_ZONE
#define CAMPUS_ZONE

#include "CampusComponent.h"

#include <vector>

class CampusZone : public CampusComponent {
    private:
        vector<CampusComponent*> components;
    
    public:
        CampusZone(string name);
        ~CampusZone();
        void add(CampusComponent* component) override;
        void remove(int code) override;
        CampusComponent* get(int code) override;
        void restrictAccess() override;
        void restoreAccess() override;
};

#endif