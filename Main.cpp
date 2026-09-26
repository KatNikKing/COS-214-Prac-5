#include <iostream>

#include "EmergencyDesk.h"

#include "Service.h"
#include "AlertService.h"

#include "Coordinator.h"
#include "CampusCoordinator.h"

#include "ResponseService.h"
#include "SecurityService.h"
#include "MedicalService.h"
#include "FacilitiesService.h"

#include "AccessControlService.h"
#include "AccessControlAdapter.h"
#include "LegacyAccessControlSystem.h"

#include "OperatorConsole.h"
#include "Command.h" //Abstract
#include "HandleIncidentCommand.h"
#include "SendAlertCommand.h"
#include "RestoreAccessCommand.h"
#include "RestrictAccessCommand.h"
#include "DispatchUnitCommand.h"

#include "CampusZone.h"
#include "CampusComponent.h"
#include "CampusUnit.h"

#include "Report.h" //Weird

#include "ResponseUnit.h"
#include "UnitStatus.h" //Abstract, child classes here too

#include "Incident.h"
#include "IncidentStatus.h" //Abstract, child classes here too
//Lordy lordy lord almighty

int main(){
    //Makin a big ol campus
    CampusZone* campus = new CampusZone("Main Campus");

    CampusZone* northCampus = new CampusZone("North Campus");
    CampusZone* engineeringBuilding = new CampusZone("Engineering Building");
    CampusUnit* serverRoom   = new CampusUnit("IT Server Room");
    CampusUnit* engLibrary   = new CampusUnit("Engineering Library");
    CampusUnit* lectureHall1 = new CampusUnit("Lecture Hall 1");
    engineeringBuilding->add(serverRoom);
    engineeringBuilding->add(engLibrary);
    engineeringBuilding->add(lectureHall1);

    CampusZone* scienceBuilding = new CampusZone("Science Building");
    CampusUnit* chemLab   = new CampusUnit("Chemistry Lab");
    CampusUnit* physicsLab = new CampusUnit("Physics Lab");
    scienceBuilding->add(chemLab);
    scienceBuilding->add(physicsLab);

    northCampus->add(engineeringBuilding);
    northCampus->add(scienceBuilding);

    CampusZone* southCampus = new CampusZone("South Campus");
    CampusZone* residenceHalls = new CampusZone("Residence Halls");
    CampusUnit* resHallA = new CampusUnit("Res Hall A");
    CampusUnit* resHallB = new CampusUnit("Res Hall B");
    residenceHalls->add(resHallA);
    residenceHalls->add(resHallB);

    CampusZone* sportsComplex = new CampusZone("Sports Complex");
    CampusUnit* gymnasium = new CampusUnit("Gymnasium");
    CampusUnit* pool      = new CampusUnit("Swimming Pool");
    sportsComplex->add(gymnasium);
    sportsComplex->add(pool);

    southCampus->add(residenceHalls);
    southCampus->add(sportsComplex);

    CampusZone* centralCampus = new CampusZone("Central Campus");
    CampusUnit* mainLibrary   = new CampusUnit("Main Library");
    CampusUnit* studentCenter = new CampusUnit("Student Center");
    CampusUnit* adminBuilding = new CampusUnit("Admin Building");
    centralCampus->add(mainLibrary);
    centralCampus->add(studentCenter);
    centralCampus->add(adminBuilding);

    campus->add(northCampus);
    campus->add(southCampus);
    campus->add(centralCampus);

    //Make units and services (ResponseServices)
    SecurityService security; 
    ResponseUnit* securityUnit = new ResponseUnit("IBS Security", &security);
    security.addUnit(securityUnit);

    MedicalService medic; 
    ResponseUnit* medicalUnit = new ResponseUnit("ABS Medical services", &medic);
    medic.addUnit(medicalUnit);

    FacilitiesService facilities;
    ResponseUnit* facilityUnit = new ResponseUnit("TukTuk central", &facilities);
    facilities.addUnit(facilityUnit);

    //Other services
    AlertService* alerts = new AlertService();
    AccessControlService* accessControl = new AccessControlAdapter(campus);

    //Adding them
    Coordinator* c = new CampusCoordinator();
    c->addService(&security);
    c->addService(&medic);
    c->addService(&facilities);
    c->addService(alerts);
    c->addService(accessControl);

    //New emergency desk
    OperatorConsole* oc = new OperatorConsole(); 
    //EmergencyDesk* emDesk = new EmergencyDesk(c, oc, &security, &medic, &facilities, accessControl, alerts);

}
