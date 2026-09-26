#include "SecurityService.h"
#include "ResponseUnit.h"

void SecurityService::receiveReport(Report report) {
    if (report.type == ReportType::SECURITY_REQUIRED) {
        cout << "Attempting security response unit dispatch...\n";
        dispatchUnit(report.incident, report.affectedArea);
    }

    else if (report.type == ReportType::INCIDENT_REPORT_WITHDRAWN) {
        for (ResponseUnit* unit : units) {
            if (unit->getIncident() == report.incident) 
                unit->recall();
        }
    }
}

string SecurityService::toString() {
    return "Security";
}