#include "Scheduler.h"
//#include "Clock.h"
#include <iostream>

using namespace std;

Scheduler::Scheduler()
{
    Clk = new Clock;
    Clk->StartClock();
    
    //ctor
}

Scheduler::~Scheduler()
{
    //dtor
}

void Scheduler::takeProcess(vector<Process *> &ProcessQ, Clock * clk){
    cout << "Enter takeProcess" << endl;
    Scheduler::veryfirstProc = ProcessQ.front();
    int counter = 1;
    int time = 0;
    bool startProcess = false;
    
    while(!startProcess){
        if(clk->getTime()==veryfirstProc->getaT()){
            startProcess=true;
        }
    }
    
    if(startProcess){
        time = veryfirstProc->getaT();
    }
    
    while(ProcessQ.size()>0){
        
        std::lock_guard<std::mutex> lock(mu);
        tempProc = ProcessQ.front();
        cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Started" << endl;
        
        time += tempProc->getbT();
        
        while(clk->getTime()!= time){}
        
        cout << "Time : " << clk->getTime() << ", P"<< tempProc->getPID() <<" ended. " << "current thread: " << std::this_thread::get_id() << endl;
        
        for(int i = 0; i<ProcessQ.size(); i++){ //For loop to pop the front process out of the vector and shifting the objects.
            if(i<ProcessQ.size()-1){
                ProcessQ.at(i) = ProcessQ.at(i+1);
            }else{
                ProcessQ.at(i)= NULL;
            }
        }
        
        ProcessQ.pop_back();
        counter++;
        mu.unlock();
    }

}


void Scheduler::main(){
    
    //cout<< "Time: " << Clk->getTime() << endl;
    Process p1(1,1000,2500);
    Process p2(2,2500,1000);
    Process p3(3,3500,1500);
    
    //Process* ProcessList[2];
    vector<Process*> ProcessQ;
    //for (int i = 1; i<sizeof(ProcessList); i++)
    ProcessQ.push_back(&p1);
    ProcessQ.push_back(&p2);
    ProcessQ.push_back(&p3);
    
    std::thread CPU1(&Scheduler::takeProcess, this, std::ref(ProcessQ), std::ref(Clk)); // Attempting to pass Clock object to thread1
    std::thread CPU2(&Scheduler::takeProcess, this, std::ref(ProcessQ), std::ref(Clk)); // Attempting to pass Clock object to thread2
    
    //if (CPU1.joinable())
    CPU1.join();
    //if (CPU2.joinable())
    CPU2.join();
    

}