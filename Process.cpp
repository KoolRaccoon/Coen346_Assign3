#include "Process.h"
#include "Clock.h"
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

void Process::run(Process *tempProc, Clock *clk, int &timer, bool& done,bool& checkifFirsttimer)
{
	//cout << tempProc->getPID() << endl;
	//cout << timer << endl;
	int b = tempProc->getbT();
	cout << "Burst time is " << b << endl;
	cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Started by CPU" << this_thread::get_id() << endl;
	timer += tempProc->getbT();
	int a = 0;
	int c = 0;
	//cout << timer << endl;
	srand(time(NULL));
	//for (int i = 0; i < 5; i++) {
	//	a = rand() % 200;
	//	cout << a << endl;
	//}
	if (checkifFirsttimer) {
		cout << "ITS FIRST TIME" << endl;
		while(clk->getTime() != timer){
					a = rand() % 200;
			c = b - a;
			if (b > 0) {
				if (c > 0) {
					//cout << "Random number generated is " << a << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(a));
					b -= a;
					//cout << "Burst time left is " << b << endl;
					m6.lock();
					cout << "P" << tempProc->getPID() << "Finished a command at " << clk->getTime() << endl;
					m6.unlock();
				}
				else {
					cout << "Burst time left is " <<b<< endl;
					cout << "Not enough time to execute next command, sleeping for the rest of burst time. " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(b));
					b -= b;
				}
			}
		}
		done = true;
		checkifFirsttimer = false;
	}
	else if (!checkifFirsttimer) {
		while (clk->getTime() != timer) {
			a = rand() % 200;
			c = b - a;
			if (b > 0) {
				if (c > 0) {
					//cout << "Random number generated is " << a << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(a));
					b -= a;
					//cout << "Burst time left is " << b << endl;
					m6.lock();
					cout << "P" << tempProc->getPID() << "Finished a command at " << clk->getTime() << endl;
					m6.unlock();
				}
				else {
					cout << "Burst time left is " <<b<< endl;
					cout << "Not enough time to execute next command, sleeping for the rest of burst time. " << endl;
					std::this_thread::sleep_for(std::chrono::milliseconds(b));
					b -= b;
				}
			}
			//else {
			//	std::this_thread::sleep_for(std::chrono::milliseconds(b));
			//	cout << "Burst time will reach negative, do nothing, just sleep" << endl;
			//	b -= b;
			//}
			//while (clk->getTime() != timer) {
			//

		}
	}
	//cout << clk->getTime() << endl;
	//while(clk->getTime()!=timer){
		cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Ended by CPU" << this_thread::get_id() << endl;
		done = true;
		//}

	}



void Process::start(Process * tempProc, Clock * clk, int &timer, bool& done, bool& checkifFirsttimer)
{
	t = new std::thread(&Process::run, this, std::ref(tempProc), std::ref(clk), std::ref(timer), std::ref(done), std::ref(checkifFirsttimer));
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

int Process::getPID(){
    return PID;
}

Process::~Process()
{
    //dtor
}
