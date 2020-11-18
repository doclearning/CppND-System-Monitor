#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;
using namespace processData;

// TODO: Return pid instead of 0
int Process::Pid() { return pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

    return cpuUtilization;
}

void Process::UpdateCpuUtilization(long totalProcessorJiffies){

    

    //totalProcessorUtilization = totalProcessorUtilizationIn;

    UpdateData(LinuxParser::CpuUtilization(pid));

    long currentProcessJiffies = currentData.Utime() + currentData.Stime();
    //currentData.TotalProcessorCache = totalProcessorJiffies;

    long divisor = (totalProcessorJiffies-previousProcessorJiffies);

    //std::cout << "("<< totalProcessorJiffies <<  "," << previousProcessorJiffies << ")\n";

    if(divisor == 0){
        return;
    }

    //std::cout << "div("<< divisor << ")\n";

    //std::cout << "("<< currentProcessJiffies <<  "," << previousProcessJiffies << ")\n";

    if(hasPreviousData)
        cpuUtilization = (currentProcessJiffies - previousProcessJiffies)/divisor;


    hasPreviousData = true;

    previousProcessJiffies = currentProcessJiffies;
    previousProcessorJiffies = totalProcessorJiffies;

    /
    //Something really strange here. previous values are not getting set, so the this whole algorithim doesn't work
    //A lead is that Update seems to run twice in ProcessContainer, meaning that there might be two copies of each process. Wtf?
    //There's also a segmentation fault when a process is killed... need to remove them from the list.

    //std::cout << "("<< totalProcessorJiffies <<  "," << previousProcessorJiffies << ")\n";
}

void Process::UpdateData(vector<string> cpuStrings){

    //std::swap(currentData, previousData);
    currentData.Update(cpuStrings);
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

bool Process::operator<(const Process& other) const { 
    return this->cpuUtilization < other.cpuUtilization;
}
