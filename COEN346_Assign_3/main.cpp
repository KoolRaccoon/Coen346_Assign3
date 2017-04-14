#include <iostream>
#include "Process.h"
#include <vector>
#include <thread>
#include "Scheduler.h"
#include "Clock.h"

using namespace std;

//void takeProcess(vector<Process*> &ProcessQ, Clock clk); //Trying to pass in Clock object. Doesn't work...
/* Maybe you shouldn't pass Clock clk, but just "clk" instead since you're not defining the function, only declaring it*/
void takeProcess(vector<Process*> &ProcessQ);
Process* tempProc;


// Right now, I initiated the clock object. However, when I try to pass it to the function, it crashes. Idk what the issue is.
// std::ref( ) wraps the object we're passing so that it is passed by reference, because threads by nature takes a copy of the object instead of actual, thus it won't reflect actual object. Need tlo pass by
int main()
{
    Clock clk;
    clk.StartClock();
    cout<< "Time: " << clk.getTime() <<endl;
    Process *pt1;
    Process *pt2;
    Process p1(1000,2500);
    Process p2(2500,1000);
    Process p3(3500,1500);

    Process* ProcessList[2];

    vector<Process*> ProcessQ;
    ProcessQ.push_back(&p1);
    ProcessQ.push_back(&p2);
    ProcessQ.push_back(&p3);

//    std::thread mythread(&takeProcess, std::ref(ProcessQ), std::ref(clk)); // Attempting to passe Clock object to thread
    std::thread mythread(&takeProcess, std::ref(ProcessQ));
    for (int i = 0; i<10; i++){
        cout <<"Printing from main thread"<<endl;
    }
    mythread.join();

/*    ProcessList[0] = p1;
    ProcessList[1] = p2;
    pt1 = & ProcessList[0];
    pt2 = & ProcessList[1];

    cout << "Process pointer 1 is pointing at index 0 and its process' arrival time is " << pt1->getaT() << endl;
    cout << "Process pointer 2 is pointing at index 1, and its process' arrival time is " << pt2->getaT() <<endl;
*/    return 0;
}

void takeProcess(vector<Process*> &ProcessQ/*, Clock clk*/){
    int counter = 1;
    while(ProcessQ.size()>0){
            cout << "Function ran: " << counter << " times" << endl;
    tempProc = ProcessQ.front();

    cout << tempProc->getbT()<<endl;

    cout << "Vector ProcessQ is of size: " << ProcessQ.size() << endl;
    for(int i = 0; i<ProcessQ.size(); i++){
        if(i<ProcessQ.size()-1){
        ProcessQ.at(i) = ProcessQ.at(i+1);
        }else{
        ProcessQ.at(i)= NULL;
        }
    }

    ProcessQ.pop_back();

    cout << "Vector ProcessQ is of size: " << ProcessQ.size() << endl;
    counter++;
    }
}
