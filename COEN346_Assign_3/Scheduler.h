#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "process.h"

using namespace std;

class Scheduler
{
    public:
        Scheduler();
        virtual ~Scheduler();
        vector<Process*> ProcessQ;

    protected:

    private:
};

#endif // SCHEDULER_H
