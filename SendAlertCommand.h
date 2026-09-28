#ifndef SEND_ALERT_COMMAND_H
#define SEND_ALERT_COMMAND_H

#include <string>
#include "Command.h"

class AlertService;

class SendAlertCommand : public Command {
    public:
        SendAlertCommand(AlertService* alerts, const std::string& message);
        ~SendAlertCommand() override;
        void execute() override;
        void undo() override;
        std::string describe() const override;

    private:
        AlertService* alerts;
        std::string message;
};

#endif // SEND_ALERT_COMMAND_H