#pragma once
#include <string>

using namespace std;

class Incident;

class IncidentStatus {
    public:
        virtual ~IncidentStatus() = default;
        virtual void activate(Incident* incident) = 0;
        virtual void resolve(Incident* incident) = 0;
        virtual void cancel(Incident* incident) = 0;
        virtual string getName() = 0;
};

class Reported : public IncidentStatus {
    public:
        void activate(Incident* incident) override;
        void resolve(Incident* incident) override;
        void cancel(Incident* incident) override;
        string getName() override { return "reported"; }
};

class Active : public IncidentStatus {
    public:
        void activate(Incident* incident) override;
        void resolve(Incident* incident) override;
        void cancel(Incident* incident) override;
        string getName() override { return "active"; }
};

class Resolved : public IncidentStatus {
    public:
        void activate(Incident* incident) override;
        void resolve(Incident* incident) override;
        void cancel(Incident* incident) override;
        string getName() override { return "resolved"; }
};

class Cancelled : public IncidentStatus {
    public:
        void activate(Incident* incident) override;
        void resolve(Incident* incident) override;
        void cancel(Incident* incident) override;
        string getName() override { return "cancelled"; }
};