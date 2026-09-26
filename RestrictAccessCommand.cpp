#include "RestrictAccessCommand.h"
#include "AccessControlService.h"
#include "CampusComponent.h"

RestrictAccessCommand::RestrictAccessCommand(AccessControlService* access, CampusComponent* area)
    : access(access), area(area), wasRestricted(false) {}

RestrictAccessCommand::~RestrictAccessCommand() {}

void RestrictAccessCommand::execute() {
    wasRestricted = area->accessIsRestricted();
    access->restrictAccess(area);
}

void RestrictAccessCommand::undo() {
    if (!wasRestricted) {
        access->restoreAccess(area);
    }
}

std::string RestrictAccessCommand::describe() const {
    return "Restrict access to " + area->getName();
}