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

    std::cout<<"\n\n--------------------------------------------------\n";
    std::cout<<"Setting up the Campus\n";
    std::cout<<"--------------------------------------------------\n\n";

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

    std::cout<<"\n\n--------------------------------------------------\n";
    std::cout<<"Making units and services\n";
    std::cout<<"--------------------------------------------------\n\n";

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

    //Empty Coordinator - services are only added once the EmergencyDesk registers them below
    Coordinator* c = new CampusCoordinator();

    //New emergency desk
    OperatorConsole* oc = new OperatorConsole(); 
    EmergencyDesk* emDesk = new EmergencyDesk(c, oc);

    //Adding services to the emergencyDesk
    emDesk->registerService(&security);
    emDesk->registerService(&medic);
    emDesk->registerService(&facilities);
    emDesk->registerService(alerts);
    emDesk->registerService(accessControl);

    std::cout<<"\n\n--------------------------------------------------\n";
    std::cout<<"Running Incident scenario no. 1 (Respond to fire)\n";
    std::cout<<"--------------------------------------------------\n\n";


    //Incident no 1: student had a heart-attack at resHallA, dispatch medical
    Incident* HeartAttackAtResA = new Incident(1000, resHallA, "A student had a heart attack at resHallA", new Reported);
    std::cout<<"Responding to Fire method: \n";
    emDesk->respondToFire(HeartAttackAtResA);

    std::cout<<"\n[Main] Operator decides to stand down the last two actions taken...\n";
    emDesk->standDown(2);

    std::cout<<"\n\n--------------------------------------------------\n";
    std::cout<<"Running Incident scenario no. 2 (HandleIncident)\n";
    std::cout<<"--------------------------------------------------\n\n";

    Incident* HellhoundsInChemLab = new Incident(1001, chemLab, "Satan's dogs got loose again and are trashing the chem lab", new Reported);
    Report* r1 = new Report(HellhoundsInChemLab, chemLab, ReportType::SECURITY_REQUIRED, "Hellhounds loose is chem lab", true);
    Report* r2 = new Report(HellhoundsInChemLab, physicsLab, ReportType::SECURITY_REQUIRED, "Hellhounds have moved to physics lab", true);
    HellhoundsInChemLab->addReport(*r1);
    HellhoundsInChemLab->addReport(*r2);

    emDesk->handleIncident(HellhoundsInChemLab);

    std::cout<<"\n\n--------------------------------------------------\n";
    std::cout<<"Running Incident scenario no. 3 (Direct Coordinator notify + mid-incident unit reports)\n";
    std::cout<<"--------------------------------------------------\n\n";

    //Incident no 3: gas leak at the Gymnasium, reported straight to the Coordinator (bypassing the EmergencyDesk)
    Incident* GasLeakAtGym = new Incident(1002, gymnasium, "A gas leak has been detected in the Gymnasium", new Reported);
    Report* r3 = new Report(GasLeakAtGym, gymnasium, ReportType::SECURITY_REQUIRED, "Cordoning off the Gymnasium", true);
    Report* r4 = new Report(GasLeakAtGym, gymnasium, ReportType::FACILITIES_REQUIRED, "Facilities needed to shut off the gas line", false);
    GasLeakAtGym->addReport(*r3);
    GasLeakAtGym->addReport(*r4);

    GasLeakAtGym->activate();
    std::cout<<"[Main] Notifying the Coordinator directly with an incident reported report...\n";
    c->notify(Report(GasLeakAtGym, GasLeakAtGym->getLocation(), ReportType::INCIDENT_REPORTED));

    std::cout<<"\n[Main] Dispatched units reporting changes mid-incident...\n";
    Report* r5 = new Report(GasLeakAtGym, gymnasium, ReportType::AREA_UNSAFE, "Gas fumes spreading fast, area unsafe", true);
    securityUnit->report(*r5);

    Report* r6 = new Report(GasLeakAtGym, gymnasium, ReportType::EVACUATION_REQUIRED, "Leak worsening, evacuation required", true);
    facilityUnit->report(*r6);

    std::cout<<"\n[Main] Standing dispatched units down...\n";
    securityUnit->recall();
    facilityUnit->recall();
    GasLeakAtGym->resolve();

    std::cout<<"\n\n--------------------------------------------------\n";
    std::cout<<"Cleaning up pointers\n";
    std::cout<<"--------------------------------------------------\n\n";


    delete emDesk;
    delete oc;
    delete c;
    delete alerts;
    delete accessControl;
    delete HeartAttackAtResA;
    delete HellhoundsInChemLab;
    delete r1;
    delete r2;
    delete GasLeakAtGym;
    delete r3;
    delete r4;
    delete r5;
    delete r6;
    delete campus;
}