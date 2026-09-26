#include "SendAlertCommand.h"
#include "AlertService.h"

SendAlertCommand::SendAlertCommand(AlertService* alerts, const std::string& message)
    : alerts(alerts), message(message) {}

SendAlertCommand::~SendAlertCommand() {}

void SendAlertCommand::execute() {
    alerts->sendAlert(message);
}

void SendAlertCommand::undo() {
    alerts->sendAlert("ALL CLEAR: " + message);
}

std::string SendAlertCommand::describe() const {
    return "Send alert: " + message;
}