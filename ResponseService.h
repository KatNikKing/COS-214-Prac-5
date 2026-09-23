#ifndef RESPONSE_SERVICE
#define RESPONSE_SERVICE

#include "Service.h"

class ResponseUnit;

class ResponseService : public Service {
    private:
        vector<ResponseUnit*> units;

    public:
        virtual ~ResponseService();
        void receiveReport(Report report) = 0;
        ResponseUnit* dispatchUnit(Incident* incident, CampusComponent* location = nullptr);
        void recallUnit(string name);
        void addUnit(ResponseUnit* unit);
        void removeUnit(string name);
};

#endif