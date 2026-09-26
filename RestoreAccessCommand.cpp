#include "RestoreAccessCommand.h"
#include "AccessControlService.h"
#include "CampusComponent.h"

RestoreAccessCommand::RestoreAccessCommand(AccessControlService* access, CampusComponent* area)
    : access(access), area(area), wasRestricted(false) {}

RestoreAccessCommand::~RestoreAccessCommand() {}

void RestoreAccessCommand::execute() {
    wasRestricted = area->accessRestricted();
    access->restoreAccess(area);
}

void RestoreAccessCommand::undo() {
    if (wasRestricted) {
        access->restrictAccess(area);
    }
}

std::string RestoreAccessCommand::describe() const {
    return "Restore access to " + area->getName();
}