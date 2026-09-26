#include "Coordinator.h"

void Coordinator::addService(Service* service) {
    if (service != nullptr) {
        bool exists = false;
        for (Service* s : services) {
            if (s == service) {
                exists = true;
                break;
            }
        }

        if (!exists)
            services.push_back(service);
    }       
}

void Coordinator::removeService(Service* service) {
    if (service != nullptr) {
        for (vector<Service*>::iterator it = services.begin(); it != services.end(); it++) {
            if (*it == service) {
                services.erase(it);
                break;
            }
        }
    }    
}

void Coordinator::removeAllServices() {
    services.clear();
}