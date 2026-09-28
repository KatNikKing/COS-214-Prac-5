#include "CampusCoordinator.h"
#include "Service.h"
#include "SecurityService.h"
#include "MedicalService.h"
#include "FacilitiesService.h"
#include "AlertService.h"
#include "AccessControlService.h"

void CampusCoordinator::notify(Report report) {
    if (report.incident == nullptr) return;
    if (report.type == ReportType::INCIDENT_REPORTED) {
        for (Report report : report.incident->reports)
            notify(report);
    }
    else {
        for (Service* service : services)
            service->receiveReport(report);
    }
}