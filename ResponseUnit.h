#ifndef RESPONSE_UNIT
#define RESPONSE_UNIT

#include "ResponseService.h"
#include "UnitStatus.h"

class ResponseUnit {
    private:
        string name;
        UnitStatus* status;
        Incident* incident;
        CampusComponent* location;
        ResponseService* service;

    public:
        ResponseUnit(string name, ResponseService* service);
        ~ResponseUnit();
        void dispatch(Incident* incident, CampusComponent* location);
        void operate();
        void recall(bool avail = true);
        void performDuty();
        void report(Report report);
        string getName();
        void setStatus(UnitStatus* status);
        UnitStatus* getStatus();
        Incident* getIncident();
        CampusComponent* getLocation();
        ResponseService* getService();
};

#endif