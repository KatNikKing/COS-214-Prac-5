#ifndef SERVICE
#define SERVICE

#include "Coordinator.h"

class Service {
    private: 
        Coordinator* coordinator = nullptr;

    public:
        virtual ~Service() = default;
        void registerService(Coordinator* coordinator);
        void unregister();
        virtual void receiveReport(Report report) = 0;
        void report(Report report);
};

#endif