#include "CampusCoordinator.h"
#include "Service.h"
#include "SecurityService.h"
#include "MedicalService.h"
#include "FacilitiesService.h"
#include "AlertService.h"
#include "AccessControlService.h"

void CampusCoordinator::notify(Report report) {
    switch (report.type) {
        case ReportType::SECURITY_REQUIRED:
            for (Service* service : services) {
                SecurityService* ss = dynamic_cast<SecurityService*>(service);
                if (ss != nullptr) {
                    ss->receiveReport(report);
                    return;
                }
            }
            cout << "Security Service unavailable.\n";
            return;

        case ReportType::MEDICAL_REQUIRED:
            for (Service* service : services) {
                MedicalService* ss = dynamic_cast<MedicalService*>(service);
                if (ss != nullptr) {
                    ss->receiveReport(report);
                    return;
                }
            }
            cout << "Medical Service unavailable.\n";
            return;

        case ReportType::FACILITIES_REQUIRED:
            for (Service* service : services) {
                FacilitiesService* ss = dynamic_cast<FacilitiesService*>(service);
                if (ss != nullptr) {
                    ss->receiveReport(report);
                    return;
                }
            }
            cout << "Facilities Service unavailable.\n";
            return;

        case ReportType::ALERT_REQUIRED:
            for (Service* service : services) {
                AlertService* ss = dynamic_cast<AlertService*>(service);
                if (ss != nullptr) {
                    ss->receiveReport(report);
                    return;
                }
            }
            cout << "Alert Service unavailable.\n";
            return;

        case ReportType::ACCESS_CONTROL_REQUIRED:
            for (Service* service : services) {
                AccessControlService* ss = dynamic_cast<AccessControlService*>(service);
                if (ss != nullptr) {
                    ss->receiveReport(report);
                    return;
                }
            }
            cout << "Access Control Service unavailable.\n";
            return;

        case ReportType::AREA_UNSAFE:
            bool found = false;
            for (Service* service : services) {
                FacilitiesService* ss = dynamic_cast<FacilitiesService*>(service);
                if (ss != nullptr) {
                    found = true;
                    ss->receiveReport(report);
                    break;
                }
            }
            if (!found) cout << "Facilities Service unavailable.\n";
            
            found = false;
            for (Service* service : services) {
                AccessControlService* ss = dynamic_cast<AccessControlService*>(service);
                if (ss != nullptr) {
                    found = true;
                    ss->receiveReport(report);
                    break;
                }
            }
            if (!found) cout << "Access Control Service unavailable.\n";

            found = false;
            for (Service* service : services) {
                AlertService* ss = dynamic_cast<AlertService*>(service);
                if (ss != nullptr) {
                    found = true;
                    ss->receiveReport(report);
                    return;
                }
            }
            if (!found) cout << "Alert Service unavailable.\n";
            return;

        case ReportType::EVACUATION_REQUIRED:
            bool found = false;
            for (Service* service : services) {
                FacilitiesService* ss = dynamic_cast<FacilitiesService*>(service);
                if (ss != nullptr) {
                    found = true;
                    ss->receiveReport(report);
                    break;
                }
            }
            if (!found) cout << "Facilities Service unavailable.\n";
            
            found = false;
            for (Service* service : services) {
                AccessControlService* ss = dynamic_cast<AccessControlService*>(service);
                if (ss != nullptr) {
                    found = true;
                    ss->receiveReport(report);
                    break;
                }
            }
            if (!found) cout << "Access Control Service unavailable.\n";

            found = false;
            for (Service* service : services) {
                AlertService* ss = dynamic_cast<AlertService*>(service);
                if (ss != nullptr) {
                    found = true;
                    ss->receiveReport(report);
                    return;
                }
            }
            if (!found) cout << "Alert Service unavailable.\n";
            return;
    }

    if (report.type == ReportType::INCIDENT_REPORTED) {

    }

    if (report.type == ReportType::INCIDENT_REPORT_WITHDRAWN) {

    }
}