#include "Service.h"

void Service::registerService(Coordinator* coordinator) {
    if (coordinator != nullptr) {
        this->coordinator = coordinator;
        this->coordinator->addService(this);
    }
}

void Service::unregister() {
    if (coordinator != nullptr) {
        coordinator->removeService(this);
        coordinator = nullptr;
    }
}
void Service::report(Report report) {
    if (coordinator != nullptr) {
        coordinator->notify(report);
    }
}