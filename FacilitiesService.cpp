#include "FacilitiesService.h"
#include "ResponseUnit.h"

void FacilitiesService::receiveReport(Report report) {
    if (report.type == ReportType::FACILITIES_REQUIRED ||
        report.type == ReportType::AREA_UNSAFE ||
        report.type == ReportType::EVACUATION_REQUIRED) {
            cout << "Attempting facilities response unit dispatch...\n";
            dispatchUnit(report.incident, report.affectedArea);
    }

    else if (report.type == ReportType::INCIDENT_REPORT_WITHDRAWN) {
        for (ResponseUnit* unit : units) {
            if (unit->getIncident() == report.incident) 
                unit->recall();
        }
    }
}

string FacilitiesService::toString() {
    return "Facilities";
}