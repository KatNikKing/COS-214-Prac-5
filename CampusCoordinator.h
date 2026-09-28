#ifndef CAMPUS_COORDINATOR
#define CAMPUS_COORDINATOR

#include "Coordinator.h"

class CampusCoordinator : public Coordinator {
    public:
        void notify(Report report) override;
};

#endif