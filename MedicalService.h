#ifndef MEDICAL_SERVICE
#define MEDICAL_SERVICE

#include "ResponseService.h"

class MedicalService : public ResponseService {
    public:
        void receiveReport(Report report) override;
};

#endif