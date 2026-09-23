#include "SecurityService.h"

void SecurityService::receiveReport(Report report) {
    if (report.type == ReportType::SECURITY_REQUIRED) {
        cout << "Attempting security response unit dispatch...\n";
        dispatchUnit(report.incident, report.affectedArea);
    }
}