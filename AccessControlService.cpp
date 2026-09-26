#include "AccessControlService.h"

void AccessControlService::receiveReport(Report report) {
    if (report.type == ReportType::ALERT_REQUIRED ||
        report.type == ReportType::AREA_UNSAFE ||
        report.type == ReportType::EVACUATION_REQUIRED) {
            if (report.restrictAccess)
                restrictAccess(report.affectedArea);
            else
                restoreAccess(report.affectedArea);
    }
}

void AccessControlService::restrictAccess(CampusComponent* affectedArea) {
    affectedArea->restrictAccess();
}

void AccessControlService::restoreAccess(CampusComponent* affectedArea) {
    affectedArea->restoreAccess();
}