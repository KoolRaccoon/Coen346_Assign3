#ifndef PROCESS_H
#define PROCESS_H
#include "Clock.h"
#include "Memory.h"
#include "MMU.h"
#include <vector>
#include <thread>

using namespace std;

class Process
{
    public:
		Clock *Clk;
        Process();
        virtual ~Process();
        Process(int, int, int);
		void run(Process*, Clock*, int&, bool&,bool&, vector<Memory*>&);
		void start(Process*, Clock*, int&,bool&,bool&, vector<Memory*>&);
        void setaT(int);
        void setbT(int);
        void setPID(int);
        int getPID();
        int getaT();
        int getbT();

    protected:

    private:
        int Arrival_Time;
        int Burst_Time;
        int PID;
		std::thread * t;
};

#endif // PROCESS_H
