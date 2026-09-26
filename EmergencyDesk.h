#ifndef EMERGENCY_DESK_H
#define EMERGENCY_DESK_H

class Coordinator;
class OperatorConsole;
class ResponseService;
class AccessControlService;
class AlertService;
class Incident;
class CampusComponent;

class EmergencyDesk {
    public:
        EmergencyDesk(Coordinator* coordinator, OperatorConsole* console, ResponseService* security, ResponseService* medical, 
                    ResponseService* facilities, AccessControlService* access, AlertService* alerts);
        ~EmergencyDesk();
        int respondToFire(Incident* incident, CampusComponent* area);
        int respondToMedical(Incident* incident, CampusComponent* area, bool alertCampus);
        void standDown(int steps);

    private:
        Coordinator* coordinator;
        OperatorConsole* console;
        ResponseService* security;
        ResponseService* medical;
        ResponseService* facilities;
        AccessControlService* access;
        AlertService* alerts;
};

#endif // EMERGENCY_DESK_H