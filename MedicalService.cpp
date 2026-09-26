#include "MedicalService.h"
#include "ResponseUnit.h"

void MedicalService::receiveReport(Report report) {
    if (report.type == ReportType::MEDICAL_REQUIRED) {
        cout << "Attempting medical response unit dispatch...\n";
        dispatchUnit(report.incident, report.affectedArea);
    }

    else if (report.type == ReportType::INCIDENT_REPORT_WITHDRAWN) {
        for (ResponseUnit* unit : units) {
            if (unit->getIncident() == report.incident) 
                unit->recall();
        }
    }
}