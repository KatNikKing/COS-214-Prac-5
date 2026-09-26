#ifndef EMERGENCY_DESK_H
#define EMERGENCY_DESK_H

#include "Coordinator.h"
#include "OperatorConsole.h"
#include "SecurityService.h"
#include "MedicalService.h"
#include "FacilitiesService.h"
#include "AccessControlService.h"
#include "AlertService.h"
#include "Incident.h"
#include "CampusComponent.h"

class EmergencyDesk {
    private:
        Coordinator* coordinator;
        OperatorConsole* console;
        SecurityService* security;
        MedicalService* medical;
        FacilitiesService* facilities;
        AccessControlService* access;
        AlertService* alerts;
        Incident* currentIncident;
        vector<ResponseUnit*> dispatchedUnits;

    public:
        EmergencyDesk(Coordinator* coordinator);
        ~EmergencyDesk();
        int handleIncident(Incident* incident);
        int respondToFire(Incident* incident);
        void standDown(int steps);
        bool manageIncident(Incident* incident);
        void resolveIncident();
        vector<ResponseUnit*> getDispatchedUnits();
        bool registerService(SecurityService* service);
        bool registerService(MedicalService* service);
        bool registerService(FacilitiesService* service);
        bool registerService(AccessControlService* service);
        bool registerService(AlertService* service);
        
};

#endif // EMERGENCY_DESK_H