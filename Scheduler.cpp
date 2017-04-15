#include "Scheduler.h"
//#include "Clock.h"
#include <iostream>

using namespace std;

Process* tempProc;
mutex mu1;
mutex mu2;
mutex mu3;

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
	bool firstProcessPicked = false;
	int time = 0;
	bool startProcess = false;
	Process* veryfirstProcOfCPU;
	//cout << this_thread::get_id() << "Entered takeProcess" <<endl;
	while (ProcessQ.size()>0) {
		if (!firstProcessPicked) {
			//cout << this_thread::get_id() << "firstProcessPicked check"<<endl;
			mu1.lock();
			//cout << this_thread::get_id() << "Locked mutex"<<endl;
			veryfirstProcOfCPU = ProcessQ.front();
			for (int i = 0; i<ProcessQ.size(); i++) { //For loop to pop the front process out of the vector and shifting the objects.
				if (i<ProcessQ.size() - 1) {
					ProcessQ.at(i) = ProcessQ.at(i + 1);
				}
				else {
					ProcessQ.at(i) = NULL;
				}
			}

			ProcessQ.pop_back();
			//cout << this_thread::get_id() << "P" << veryfirstProcOfCPU->getPID()<<endl;
			firstProcessPicked = true;
			mu1.unlock();
			//cout << this_thread::get_id() << "Unlocked mutex"<<endl;
			//Checks for VERY FIRST arrival time to start executing process
			while (!startProcess) {
				if (clk->getTime() == veryfirstProcOfCPU->getaT()) {
					//cout <<veryfirstProcOfCPU->getaT();
					startProcess = true;
					time = veryfirstProcOfCPU->getaT();
				}
			}
			cout << "Time : " << clk->getTime() << ", P" << veryfirstProcOfCPU->getPID() << " Started by CPU" << this_thread::get_id() << endl;
			time += veryfirstProcOfCPU->getbT();
			while (clk->getTime() != time) {

			}

			cout << "Time : " << clk->getTime() << ", P" << veryfirstProcOfCPU->getPID() << " Ended by CPU" << std::this_thread::get_id() << endl;


		}
		else {
			//cout << this_thread::get_id() << "Entered else" <<endl;
			mu2.lock();
			//cout << this_thread::get_id() << "Locked mutex2" <<endl;
			tempProc = ProcessQ.front();
			for (int i = 0; i<ProcessQ.size(); i++) { //For loop to pop the front process out of the vector and shifting the objects.
				if (i<ProcessQ.size() - 1) {
					ProcessQ.at(i) = ProcessQ.at(i + 1);
				}
				else {
					ProcessQ.at(i) = NULL;
				}
			}

			ProcessQ.pop_back();
			mu2.unlock();
			//cout << this_thread::get_id() << "unlocked mutex2" <<endl;

			cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Started by CPU" << this_thread::get_id() << endl;
			time += tempProc->getbT();
			while (clk->getTime() != time) {

			}

			cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Ended by CPU" << this_thread::get_id() << endl;

		}
	}
}


void Scheduler::main(){
	cout << "entered scheduler main()" << endl;
    //cout<< "Time: " << Clk->getTime() << endl;
    Process p1(1,1000,2500);
    Process p2(2,2500,20000);
    Process p3(3,3500,1500);
	Process p4(4, 5000, 2000);
    
    //Process* ProcessList[2];
    vector<Process*> ProcessQ;
    //for (int i = 1; i<sizeof(ProcessList); i++)
    ProcessQ.push_back(&p1);
    ProcessQ.push_back(&p2);
    ProcessQ.push_back(&p3);
	ProcessQ.push_back(&p4);
    
    std::thread CPU1(&Scheduler::takeProcess, this, std::ref(ProcessQ), std::ref(Clk)); // Attempting to pass Clock object to thread1
    std::thread CPU2(&Scheduler::takeProcess, this, std::ref(ProcessQ), std::ref(Clk)); // Attempting to pass Clock object to thread2
    
    //if (CPU1.joinable())
    CPU1.join();
    //if (CPU2.joinable())
    CPU2.join();
    

}
