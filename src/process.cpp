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

void Process::UpdateCpuUtilization(float TotalProcessorUtilization){

    UpdateData(LinuxParser::CpuUtilization(pid));

    currentData.TotalProcessCache = currentData.Utime() + currentData.Stime();
    currentData.TotalProcessorCache = TotalProcessorUtilization;

    float divisor = (float)currentData.TotalProcessorCache-previousData.TotalProcessorCache;

    if(divisor == 0){
        return;
    }

    if(hasPreviousData)
        cpuUtilization = (currentData.TotalProcessCache - previousData.TotalProcessCache)/divisor;

    hasPreviousData = true;
}

void Process::UpdateData(vector<string> cpuStrings){

    std::swap(currentData, previousData);
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