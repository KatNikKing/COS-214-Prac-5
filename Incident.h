#pragma once 

#include <string>
#include <vector>
#include <algorithm>
#include "IncidentStatus.h"
#include "CampusComponent.h"

struct Report;

class Incident {
    friend class CampusCoordinator;
    private: 
        int id;
        vector<Report> reports; 
        CampusComponent* location;
        string description;
        IncidentStatus* status;
    
    public: 
        Incident(int id, CampusComponent* location, string description, IncidentStatus* status);
        ~Incident();
        void activate();
        void resolve();
        void cancel();
        void setStatus(IncidentStatus* status);
        string getStatus();
        CampusComponent* getLocation();
        int getId();
        string getDescription();
        void addReport(Report r);
        void removeReport(Report r);
};