#ifndef FACILITIES_SERVICE
#define FACILITIES_SERVICE

#include "ResponseService.h"

class FacilitiesService : public ResponseService {
    public:
        void receiveReport(Report report) override;
        string toString() override;
};

#endif