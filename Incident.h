#pragma once 

#include <string>
#include "IncidentStatus.h"
#include "CampusComponent.h"

class Incident {
    private: 
        int id;
        CampusComponent* location;
        string description;
        int severity;
        IncidentStatus* status;
    
    public: 
        Incident(int id, CampusComponent* location, string description, int severity, IncidentStatus* status);
        ~Incident();
        void activate();
        void resolve();
        void cancel();
        void setStatus(IncidentStatus* status);
        string getStatus();
        CampusComponent* getLocation();
        int getId();
};