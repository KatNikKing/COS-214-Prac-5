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
    public:
        EmergencyDesk(Coordinator* coordinator);
        ~EmergencyDesk();
        int handleIncident(Incident* incident);
        int respondToFire(Incident* incident);
        void standDown(int steps);
        bool registerService(SecurityService* service);
        bool registerService(MedicalService* service);
        bool registerService(FacilitiesService* service);
        bool registerService(AccessControlService* service);
        bool registerService(AlertService* service);
        
    private:
        Coordinator* coordinator;
        OperatorConsole* console;
        SecurityService* security;
        MedicalService* medical;
        FacilitiesService* facilities;
        AccessControlService* access;
        AlertService* alerts;
        Incident* currentIncident;
        int steps;
};

#endif // EMERGENCY_DESK_H