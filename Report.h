#ifndef REPORT
#define REPORT

#include "ReportType.h"
#include "CampusComponent.h"
#include "Incident.h"

using namespace std;

struct Report {
    CampusComponent* affectedArea;
    Incident* incident;
    string message;
    ReportType type;
    bool restrictAccess;

    Report(Incident* incident, CampusComponent* affectedArea, ReportType type, string message = "", bool restrictAccess = false) :
            affectedArea(affectedArea), incident(incident), message(message), type(type), restrictAccess(restrictAccess) {}

    bool operator==(const Report& other) {
        return affectedArea == other.affectedArea && incident == other.incident && 
               message == other.message && type == other.type && restrictAccess == other.restrictAccess;
    }
};

#endif