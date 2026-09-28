#ifndef UNIT_STATUS
#define UNIT_STATUS

#include <iostream>

using namespace std;

class UnitStatus {
    public:
        virtual ~UnitStatus() = default;
        virtual void performDuty() = 0;
};

class Available : public UnitStatus {
    public:
        void performDuty() {
            cout << "is currently on standby.\n";
        }
};

class Dispatched : public UnitStatus {
    private:
        string destination;
    public:
        Dispatched(string destination) : destination(destination) {}
        void performDuty() {
            cout << "has been dispatched to " << destination << ".\n";
        }
};

class Operating : public UnitStatus {
    public:
        void performDuty() {
            cout << "is responding to emergency.\n";
        }
};

class Unavailable : public UnitStatus {
    public:
        void performDuty() {
            cout << "is currently unavailable.\n";
        }
};



#endif