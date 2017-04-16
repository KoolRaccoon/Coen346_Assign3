#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "process.h"
#include "Clock.h"
#include "Memory.h"
#include <thread>

using namespace std;

class Scheduler
{
    
    public:
    
    Scheduler();
    virtual ~Scheduler();
    
    void main();
    void takeProcess (vector<Process*> &, Clock*);
	int Num_Process;
	int Mem_Size;
	Process ProcessArray[20];
	Memory MemoryArray[20];
	void ReadinputFile();
	void ReadMemConfigFile();
    //Process* tempProc;
    //std::thread *CPU1;
    //std::thread *CPU2;
    
    Clock *Clk;
    
    protected:

    private:
};

#endif // SCHEDULER_H
