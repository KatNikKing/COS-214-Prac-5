#ifndef COORDINATOR
#define COORDINATOR

#include "Report.h"

#include <iostream>
#include <vector>

using namespace std;

class Service;

class Coordinator {
    protected:
        vector<Service*> services;

    public:
        virtual ~Coordinator() = default;
        void addService(Service* service);
        void removeService(Service* service);
        void removeAllServices();
        virtual void notify(Report report) = 0;
};

#endif