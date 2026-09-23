#ifndef CAMPUS_COMPONENT
#define CAMPUS_COMPONENT

#include <string>

using namespace std;

class CampusComponent {
    private:
        string name;
        int code;
        static int codeCount;

    protected:
        bool accessRestricted;

    public:
        CampusComponent(string name);
        virtual ~CampusComponent() = default;
        virtual void restrictAccess() = 0;
        virtual void restoreAccess() = 0;
        virtual void add(CampusComponent* component);
        virtual void remove(int code);
        virtual CampusComponent* get(int code) = 0;
        string getName();
        bool accessIsRestricted();
        int getCode();
};

#endif