#ifndef ALERT_SERVICE
#define ALERT_SERVICE

#include "Service.h"

class AlertService : public Service {
    public:
        virtual void receiveReport(Report report) override;
        void sendAlert(string message);
};

#endif