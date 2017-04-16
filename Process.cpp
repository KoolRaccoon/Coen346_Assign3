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
	//cout << tempProc->getPID() << "Entered run()" << endl;
	//cout << tempProc->getPID() << endl;
	//cout << timer << endl;
	int b = tempProc->getbT();
	//cout << "Burst time is " << b << endl;
	cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Started by CPU" << this_thread::get_id() << endl;
	timer += tempProc->getbT();
	srand(time(NULL));

	if (checkifFirsttimer) {
		int a = 0;
		int c = 0;
		int sumOa = 0;
		int d = 0;

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
					std::this_thread::sleep_for(std::chrono::milliseconds(a));
					b -= a;
					while (clk->getTime() != (d + a)) {} ////// 
					m6.lock();
					cout << "P" << tempProc->getPID() << " Finished a command at " << clk->getTime() << endl;
					m6.unlock();
				}
				else {
					//cout << "P" << tempProc->getPID() << " Burst time left is " <<b<< endl;
					//cout << "P" << tempProc->getPID() << " Not enough time to execute next command, sleeping for the rest of burst time. " << endl;
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
		while (clk->getTime() != timer) {
			while(b>0){
			a = rand() % 200;
			sumOa += a;
			d = clk->getTime();
			c = b - a;
	//		if (b > 0) {
				if (c > 0) {

					std::this_thread::sleep_for(std::chrono::milliseconds(a));
					b -= a;
					while (clk->getTime() != (d + a)) {} ////// 
					m7.lock();
					cout << "P" << tempProc->getPID() << " Finished a command at " << clk->getTime() << endl;
					m7.unlock();
				}
				else {
					//cout << "P" << tempProc->getPID() << "'s Burst time left is " <<b<< endl;
					//cout << "Not enough time to execute next command, sleeping for the rest of burst time. " << endl;
					//std::this_thread::sleep_for(std::chrono::milliseconds(b));
					b -= b;
				}
			}

		}
	}

		cout << "Time : " << clk->getTime() << ", P" << tempProc->getPID() << " Ended by CPU" << this_thread::get_id() << endl;
		//cout << "TESTING HERE" << endl;
		done = true;
		//cout << "Bool done is now " << done << endl;
		//cout << "Program will crash." << endl;


	}



void Process::start(Process * tempProc, Clock * clk, int &timer, bool& done, bool& checkifFirsttimer)
{
	//cout << tempProc->getPID() << "Entered start()" << endl;
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
	//t->join();
    //dtor
}
