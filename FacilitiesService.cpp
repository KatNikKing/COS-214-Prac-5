#include "FacilitiesService.h"

void FacilitiesService::receiveReport(Report report) {
    if (report.type == ReportType::FACILITIES_REQUIRED ||
        report.type == ReportType::AREA_UNSAFE ||
        report.type == ReportType::EVACUATION_REQUIRED) {
            cout << "Attempting facilities response unit dispatch...\n";
            dispatchUnit(report.incident, report.affectedArea);
    }
}