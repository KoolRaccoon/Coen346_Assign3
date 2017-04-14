#ifndef PROCESS_H
#define PROCESS_H

#include <vector>

using namespace std;

class Process
{
    public:
        Process();
        virtual ~Process();
        Process(int, int);
        void setaT(int);
        void setbT(int);
        int getaT();
        int getbT();

    protected:

    private:
        int Arrival_Time;
        int Burst_Time;
};

#endif // PROCESS_H
