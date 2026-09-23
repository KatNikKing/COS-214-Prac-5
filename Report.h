#ifndef REPORT
#define REPORT

#include "ReportType.h"
#include "CampusComponent.h"

using namespace std;

class Incident;

struct Report {
    CampusComponent* affectedArea;
    Incident* incident;
    string message;
    ReportType type;
    bool restrict;

    Report(CampusComponent* affectedArea, Incident* incident, string message, ReportType type, bool restrict) :
            affectedArea(affectedArea), incident(incident), message(message), type(type), restrict(restrict) {}
};

#endif