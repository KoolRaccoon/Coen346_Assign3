#include <iostream>
#include "Process.h"
#include <vector>
#include <thread>
#include "Scheduler.h"
#include "Clock.h"
#include <mutex>
#include <fstream>

mutex mu1;
mutex mu2;
mutex mu3;

using namespace std;

void ReadFile ();
void takeProcess(vector<Process*> &ProcessQ, Clock& clk); //Trying to pass in Clock object. Doesn't work...
/* Maybe you shouldn't pass Clock clk, but just "clk" instead since you're not defining the function, only declaring it*/
Process* tempProc;
int Num_Process;
vector<Process*> ReadProcess[10];
Process ProcessArray[20];



// Right now, I initiated the clock object. However, when I try to pass it to the function, it crashes. Idk what the issue is.
// std::ref( ) wraps the object we're passing so that it is passed by reference, because threads by nature takes a copy of the object instead of actual, thus it won't reflect actual object. Need tlo pass by
int main()
{
    Clock clk;
    clk.StartClock();
    cout<< "Time: " << clk.getTime() <<endl;
    vector<Process*> ProcessQ;
    Process *pt1;
    Process *pt2;
    //Process p1(1,1000,2500);
    //Process p2(2,2500,2000);
    //Process p3(3,3500,1500);
    //Process p4(4,5000,2000);
    ReadFile();

    for(int i=0; i<Num_Process;i++){
        //cout << ProcessArray[i].getPID() << ", " << ProcessArray[i].getaT() << ", " << ProcessArray[i].getbT() << endl;
        ProcessQ.push_back(&ProcessArray[i]);
    }
    Process* ProcessList[2];
    //ProcessQ=ReadProcess;
    //for (int i = 1; i<sizeof(ProcessList); i++)
    //ProcessQ.push_back(&p1);
    //ProcessQ.push_back(&p2);
    //ProcessQ.push_back(&p3);


    std::thread CPU1(&takeProcess, std::ref(ProcessQ), std::ref(clk)); // Attempting to passe Clock object to thread1
    std::thread CPU2(&takeProcess, std::ref(ProcessQ), std::ref(clk)); // Attempting to passe Clock object to thread2

    CPU1.join();
    CPU2.join();

/*    ProcessList[0] = p1;
    ProcessList[1] = p2;
    pt1 = & ProcessList[0];
    pt2 = & ProcessList[1];

    cout << "Process pointer 1 is pointing at index 0 and its process' arrival time is " << pt1->getaT() << endl;
    cout << "Process pointer 2 is pointing at index 1, and its process' arrival time is " << pt2->getaT() <<endl;
*/    return 0;
}

void takeProcess(vector<Process*> &ProcessQ, Clock& clk){
    //cout <<"Entering takeProcess" <<endl;
    bool firstProcessPicked = false;
    int time =0;
    bool startProcess = false;
    Process* veryfirstProcOfCPU;
    //cout << this_thread::get_id() << "Entered takeProcess" <<endl;
    while(ProcessQ.size()>0){
        if(!firstProcessPicked){
                //cout << this_thread::get_id() << "firstProcessPicked check"<<endl;
                mu1.lock();
                //cout << this_thread::get_id() << "Locked mutex"<<endl;
                veryfirstProcOfCPU = ProcessQ.front();
                for(int i = 0; i<ProcessQ.size(); i++){ //For loop to pop the front process out of the vector and shifting the objects.
                if(i<ProcessQ.size()-1){
                    ProcessQ.at(i) = ProcessQ.at(i+1);
                    }else{
                        ProcessQ.at(i)= NULL;
                        }
                }

                ProcessQ.pop_back();
                //cout << this_thread::get_id() << "P" << veryfirstProcOfCPU->getPID()<<endl;
                firstProcessPicked = true;
                mu1.unlock();
                //cout << this_thread::get_id() << "Unlocked mutex"<<endl;
    //Checks for VERY FIRST arrival time to start executing process
            while(!startProcess){
                if(clk.getTime()==veryfirstProcOfCPU->getaT()){
                    //cout <<veryfirstProcOfCPU->getaT();
                startProcess=true;
                time = veryfirstProcOfCPU->getaT();
                }
            }
                cout << "Time : " << clk.getTime() << ", P" << veryfirstProcOfCPU->getPID() << " Started by CPU"<<this_thread::get_id() << endl;
                time += veryfirstProcOfCPU->getbT();
                while(clk.getTime()!= time){

                    }

                cout << "Time : " << clk.getTime() << ", P"<< veryfirstProcOfCPU->getPID() <<" Ended by CPU" << std::this_thread::get_id() << endl;


        }else{
                //cout << this_thread::get_id() << "Entered else" <<endl;
                mu2.lock();
                //cout << this_thread::get_id() << "Locked mutex2" <<endl;
                tempProc = ProcessQ.front();
                for(int i = 0; i<ProcessQ.size(); i++){ //For loop to pop the front process out of the vector and shifting the objects.
                if(i<ProcessQ.size()-1){
                ProcessQ.at(i) = ProcessQ.at(i+1);
                }else{
                ProcessQ.at(i)= NULL;
                }
                }

                ProcessQ.pop_back();
                mu2.unlock();
                //cout << this_thread::get_id() << "unlocked mutex2" <<endl;

                cout << "Time : " << clk.getTime() << ", P" << tempProc->getPID() << " Started by CPU" <<this_thread::get_id() << endl;
                time += tempProc->getbT();
                while(clk.getTime()!= time){

                    }

                cout << "Time : " << clk.getTime() << ", P"<< tempProc->getPID() <<" Ended by CPU" << this_thread::get_id() << endl;

        }
    }
    //cout << "Vector ProcessQ is of size: " << ProcessQ.size() << endl
}

void ReadFile (){

    fstream input_File;

    string File_Path = "input.txt";

    input_File.open(File_Path);
    input_File >> Num_Process;
    for(int i = 0; i<Num_Process; i++){
        int a,b,c;
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
