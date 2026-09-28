#include "AlertService.h"

void AlertService::receiveReport(Report report) {
    if (report.type == ReportType::ALERT_REQUIRED) 
        sendAlert(report.message);
    else if (report.type == ReportType::AREA_UNSAFE) 
        sendAlert("Area " + report.affectedArea->getName() + " unsafe.");
    else if (report.type == ReportType::EVACUATION_REQUIRED) 
        sendAlert("Evacuate area " + report.affectedArea->getName() + " .");
}

void AlertService::sendAlert(string message) {
    if (message == "") return;
    cout << "=====\nSENDING ALERT...\nMessage:\n" << message << "\n=====\n";
}