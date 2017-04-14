#include "Process.h"
#include "Clock.h"
#include <iostream>

using namespace std;


Process::Process()
{
    cout << "Entering ctor"<<endl;
    Arrival_Time=0;
    Burst_Time=0;
}

Process::Process(int aT, int bT){
    Arrival_Time = aT;
    Burst_Time = bT;
}

void Process::setaT(int aT){
    Arrival_Time = aT;
}

void Process::setbT(int bT){
    Burst_Time = bT;
}

int Process::getaT(){
    return Arrival_Time;
}

int Process::getbT(){
    return Burst_Time;
}

Process::~Process()
{
    //dtor
}
