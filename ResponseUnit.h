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
        void recall();
        void performDuty();
        void report(Report report);
        string getName();
        void setStatus(UnitStatus* status);
        UnitStatus* getStatus();
        CampusComponent* getLocation();
        ResponseService* getService();
};

#endif