#include "Process.h"
#include "Clock.h"
#include "Memory.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <time.h>
using namespace std;

mutex mu;
mutex mub;
mutex m6;
mutex m7;
mutex m8;
mutex m9;
mutex m5;
mutex m10;

Process::Process()
{
    Arrival_Time=0;
    Burst_Time=0;
    PID = 0;
}

Process::Process(int pid,int aT, int bT){
    Arrival_Time = aT;
    Burst_Time = bT;
    PID = pid;
}

void Process::run(Process *tempProc, Clock *clk, int &timer, bool& done,bool& checkifFirsttimer, vector<Memory*>& MemoryStorage, vector<MMU*>&Commandlist)
{
	//cout << "First Variable ID is " << MemoryStorage.at(0)->getVarID() << endl;
	//cout << "First command action is: " << Commandlist.at(0)->getActionID() << endl;
	//cout << tempProc->getPID() << "Entered run()" << endl;
	//cout << tempProc->getPID() << endl;
	//cout << timer << endl;
	int b = tempProc->getbT();
	//cout << "Burst time is " << b << endl;
	m5.lock();
	cout << "Time " << clk->getTime() << ", P" << tempProc->getPID() << " Started" << endl;
	m5.unlock();
	timer += tempProc->getbT();
	srand(time(NULL));

	if (checkifFirsttimer) {
		int a = 0;
		int c = 0;
		int sumOa = 0;
		int d = 0;
		int commandcounter=0;
		int commandsize = Commandlist.size();
		int APICall = 0;
		int valuetostore = 0;
		int varPos = 0;

		//cout << "ITS FIRST TIME" << endl;
		while(clk->getTime() < timer && b!=0){
			while(b>0){
					a = rand() % 200;
					sumOa += a;
					d = clk->getTime();
					c = b - a;
					//cout << "P" << tempProc->getPID() << "'s C: " << c << ", B: " << b << ", A: " << a << endl;
			//if (b > 0) {
				//cout << "P" << tempProc->getPID() << "'s total of BT executed "<< sumOa << endl;
				if (c > 0) {
					cout << "Time " << clk->getTime() << ", P" << tempProc->getPID() << ", " << Commandlist.at(commandcounter)->getAction() << ": Variable " << Commandlist.at(commandcounter)->getVarID() << ", Value " << Commandlist.at(commandcounter)->getToValue() << endl;
					APICall = Commandlist.at(commandcounter)->getActionID();
					if (APICall = 1) {
						valuetostore = Commandlist.at(commandcounter)->getToValue();
						varPos = Commandlist.at(commandcounter)->getVarID();
					}
					else {
						varPos = Commandlist.at(commandcounter)->getVarID();
					}
					commandcounter++;
					switch (APICall) {
					case 1:
						store(MemoryStorage, valuetostore, varPos);
						cout << MemoryStorage.at(varPos)->getValue() << endl;
						break;
					case 2:
						release(MemoryStorage, varPos);
						cout << MemoryStorage.at(varPos)->getValue() << endl;
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(a));
					b -= a;
					while (clk->getTime() != (d + a)) {} ////// 
					m6.lock();
					//cout << "P" << tempProc->getPID() << " Finished command at " << clk->getTime() << endl;
					m6.unlock();
				}
				else {
					//cout << "P" << tempProc->getPID() << " Burst time left is " <<b<< endl;
					m7.lock();
					//cout << "P" << tempProc->getPID() << " Not enough time to execute next command, sleeping for the rest of burst time. " << endl;
					m7.unlock();
					//std::this_thread::sleep_for(std::chrono::milliseconds(b));
					b -= b;
					//cout << b << endl;
				}

			
			}
		}
		done = true;
		checkifFirsttimer = false;
	}
	else if (!checkifFirsttimer) {
		int a = 0;
		int c = 0;
		int sumOa = 0;
		int d = 0;
		int commandcounter = 0;
		int APICall = 0;
		int valuetostore = 0;
		int varPos = 0;
		while (clk->getTime() != timer) {
			while(b>0){
			a = rand() % 200;
			sumOa += a;
			d = clk->getTime();
			c = b - a;
	//		if (b > 0) {
				if (c > 0) {
					cout << "Time " << clk->getTime() << ", P" << tempProc->getPID() << ", " << Commandlist.at(commandcounter)->getAction() << ": Variable " << Commandlist.at(commandcounter)->getVarID() << ", Value " << Commandlist.at(commandcounter)->getToValue() << endl;
					APICall = Commandlist.at(commandcounter)->getActionID();
					if (APICall = 1) {
						valuetostore = Commandlist.at(commandcounter)->getToValue();
						varPos = Commandlist.at(commandcounter)->getVarID();
					}
					else {
						varPos = Commandlist.at(commandcounter)->getVarID();
					}
					commandcounter++;
					switch (APICall) {
					case 1:
						store(MemoryStorage, valuetostore, varPos);
						//cout << MemoryStorage.at(varPos)->getValue() << endl;
						break;
					case 2:
						release(MemoryStorage, varPos);
						cout << MemoryStorage.at(varPos)->getValue() << endl;
						break;
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(a));
					b -= a;
					while (clk->getTime() != (d + a)) {} ////// 
					m7.lock();
					//cout << "P" << tempProc->getPID() << " Finished command at " << clk->getTime() << endl;
					m7.unlock();
				}
				else {
					//cout << "P" << tempProc->getPID() << "'s Burst time left is " <<b<< endl;
					m9.lock();
					//cout << "P" << tempProc->getPID() << " Not enough time to execute next command, sleeping for the rest of burst time. " << endl;
					m9.unlock();
					//std::this_thread::sleep_for(std::chrono::milliseconds(b));
					b -= b;
				}
			}

		}
	}
	m10.lock();
		cout << "Time " << clk->getTime() << ", P" << tempProc->getPID() << ", Terminated"/*" Ended by CPU" << this_thread::get_id()*/ << endl;
		m10.unlock();
		//cout << "TESTING HERE" << endl;
		done = true;
		//cout << "Bool done is now " << done << endl;
		//cout << "Program will crash." << endl;

	}



void Process::start(Process * tempProc, Clock * clk, int &timer, bool& done, bool& checkifFirsttimer, vector<Memory*>& MemoryStorage, vector<MMU*>& Commandlist)
{
	//cout << tempProc->getPID() << "Entered start()" << endl;
	t = new std::thread(&Process::run, this, std::ref(tempProc), std::ref(clk), std::ref(timer), std::ref(done), std::ref(checkifFirsttimer), std::ref(MemoryStorage), std::ref(Commandlist));
}

void Process::setaT(int aT){
    Arrival_Time = aT;
}

void Process::setbT(int bT){
    Burst_Time = bT;
}

void Process::setPID(int pid){
    PID = pid;
}

int Process::getaT(){
    return Arrival_Time;
}

int Process::getbT(){
    return Burst_Time;
}

void Process::store(vector<Memory*>& MemoryStorage,int valuetostore, int & varPos)
{
	MemoryStorage.at(varPos)->setValue(valuetostore);
}

void Process::release(vector<Memory*>& MemoryStorage, int varID)
{
	MemoryStorage.at(varID)->setVarID(0);
}

int Process::getPID(){
    return PID;
}

Process::~Process()
{
	//t->join();
    //dtor
}
