#ifndef SECURITY_SERVICE
#define SECURITY_SERVICE

#include "ResponseService.h"

class SecurityService : public ResponseService {
    public:
        void receiveReport(Report report) override;
        string toString() override;
};

#endif