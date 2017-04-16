#include "Scheduler.h"
#include "Clock.h"
#include <iostream>
#include <fstream>
#include "memory.h"
#include <condition_variable>
using namespace std;

mutex mu1;
mutex mu2;
mutex mu3;
mutex mup;

condition_variable cv;

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

void Scheduler::ReadinputFile() {

	fstream input_File;

	string File_Path = "input.txt";

	input_File.open(File_Path);
	input_File >> Num_Process;
	for (int i = 0; i<Num_Process; i++) {
		int a, b, c;
		input_File >> a;
		ProcessArray[i].setPID(a);
		input_File >> b;
		ProcessArray[i].setaT(b);
		input_File >> c;
		ProcessArray[i].setbT(c);

		//ReadProcess.push_back(&StoreProcess);
		//cout << ReadProcess[i]->getPID()<<" " << ReadProcess[i]->getaT() << " " << ReadProcess[i]->getbT() << endl;
	}

	input_File.close();
}

void Scheduler::ReadMemConfigFile() {

	fstream input_File;

	string File_Path = "memconfig.txt";

	input_File.open(File_Path);
	input_File >> Mem_Size;
	for (int i = 0; i < Mem_Size; i++) {
		int a = i + 1;
		MemoryArray[i].setVarID(a);
		MemoryArray[i].setAgeint(0);
		MemoryArray[i].setValue(0);
	}

	input_File.close();
}

void Scheduler::takeProcess(vector<Process *> &ProcessQ, Clock * clk){
    //cout << "Enter takeProcess 1" << endl;
	bool firstProcessPicked = false;
	int time = 0;
	bool startProcess = false;
	bool startProcesschecked = false;
	bool checkifFirsttimer = false; // UNTIL THIS PART
	bool done = false;
	Process* veryfirstProcOfCPU;
	//cout << "Enter takeProcess 2" << endl;
	while (ProcessQ.size()>0) {
		//cout << "Enter takeProcess 3" << endl;
		if (!firstProcessPicked) {
			//cout << "Enter takeProcess 4" << endl;
			checkifFirsttimer = true; 

			mu1.lock();

			veryfirstProcOfCPU = ProcessQ.front();
			for (int i = 0; i<ProcessQ.size(); i++) { //For loop to pop the front process out of the vector and shifting the objects.
				if (i<ProcessQ.size() - 1) {
					ProcessQ.at(i) = ProcessQ.at(i + 1);
				}
				else {
					ProcessQ.at(i) = NULL;
				}
			}
			//cout << "P" << veryfirstProcOfCPU->getPID() << "retrieved" << endl;
			ProcessQ.pop_back();

			firstProcessPicked = true;
			mu1.unlock();

			//Checks for VERY FIRST arrival time to start executing process
			//cout << "P" << veryfirstProcOfCPU->getPID() << "at startProcess check with bool :" << startProcess << endl;
			while (!startProcess) {
				if (clk->getTime() == veryfirstProcOfCPU->getaT()) {
					//cout <<veryfirstProcOfCPU->getaT();
					startProcess = true;
					startProcesschecked = true;
					time = veryfirstProcOfCPU->getaT();
				}
			}

			if (startProcesschecked) {
				startProcess = true;
				startProcesschecked = false;
			}

			//cout << "P" << veryfirstProcOfCPU->getPID() << "exited startProcess check with bool :" << startProcess << endl;
			// Starts here

			//cout << "Time : " << clk->getTime() << ", P" << veryfirstProcOfCPU->getPID() << " Started by CPU" << this_thread::get_id() << endl;
			//time += veryfirstProcOfCPU->getbT();
			//while (clk->getTime() != time) {
			//}
			//std::unique_lock<std::mutex> lck(mup);
			veryfirstProcOfCPU->start(veryfirstProcOfCPU, clk, time, done, checkifFirsttimer);
			//cout << "P" << veryfirstProcOfCPU->getPID()<< "Checking boolean DONE :" << done << endl;
			while (!done) {}
			//cout << "P" << veryfirstProcOfCPU->getPID() << "Exiting boolean DONE :" << done << endl;

			done = false;

			//cout << "Time : " << clk->getTime() << ", P" << veryfirstProcOfCPU->getPID() << " Ended by CPU" << std::this_thread::get_id() << endl;


		}
		else {
			//cout << "ENTERED ELSE" << endl;
			Process* tempProc;
			mu2.lock();
			tempProc = ProcessQ.front();
			for (int i = 0; i < ProcessQ.size(); i++) { //For loop to pop the front process out of the vector and shifting the objects.
				if (i < ProcessQ.size() - 1) {
					ProcessQ.at(i) = ProcessQ.at(i + 1);
				}
				else {
					ProcessQ.at(i) = NULL;
				}
			}

			ProcessQ.pop_back();
			mu2.unlock();
			//cout << this_thread::get_id() << "unlocked mutex2" <<endl;

			//cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Started by CPU" << this_thread::get_id() << endl;
			//time += tempProc->getbT();
			//while (clk->getTime() != time) {
			////tempProc->start(tempProc, clk, time);
			//}
			//cout << "Process number is " << tempProc->getPID() << endl;
			//cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Ended by CPU" << this_thread::get_id() << endl;
			done = false;
			//std::unique_lock<std::mutex> lck(mup);
			tempProc->start(tempProc, clk, time, done, checkifFirsttimer);
			while (!done) {}
			//cout << "Bool done is now " << done << endl;

		}
		cout << "ProcessQ size is " << ProcessQ.size() << endl;
	}
	//cout << "Stuck here maybe?" << endl;
}


void Scheduler::main(){
	//cout << "entered scheduler main()" << endl;

    vector<Process*> ProcessQ;

	ReadinputFile();

	for (int i = 0; i<Num_Process; i++) {
		cout << ProcessArray[i].getPID() << ", " << ProcessArray[i].getaT() << ", " << ProcessArray[i].getbT() << endl;
		ProcessQ.push_back(&ProcessArray[i]);
	}

	vector<Memory*> MemoryStorage;
	ReadMemConfigFile();
	for (int j = 0; j < Mem_Size; j++) {
		cout << MemoryArray[j].getVarID() << endl;
		MemoryStorage.push_back(&MemoryArray[j]);
	}


    
    std::thread CPU1(&Scheduler::takeProcess, this, std::ref(ProcessQ), std::ref(Clk)); // Attempting to pass Clock object to thread1
    std::thread CPU2(&Scheduler::takeProcess, this, std::ref(ProcessQ), std::ref(Clk)); // Attempting to pass Clock object to thread2
    
	//cout << "waiting to join threads" << endl;
    CPU1.join();

    CPU2.join();
    

}
