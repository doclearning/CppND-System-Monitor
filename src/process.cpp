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

int Process::Pid() { return pid; }

float Process::CpuUtilization() { 

    return cpuUtilization;
}

void Process::UpdateCpuUtilization(long currentProcessorJiffies){

    data.Update(LinuxParser::CpuUtilization(pid));

    long currentProcessJiffies = data.Utime() + data.Stime();


    float top = (float)(currentProcessJiffies - (previousProcessJiffies));
    float bottom = (float)(currentProcessorJiffies-(previousProcessorJiffies));

    if(hasPreviousData){
        if(bottom != 0)
            cpuUtilization =top/bottom;
    }

    this->hasPreviousData = true;
    this->previousProcessJiffies = currentProcessJiffies;
    this->previousProcessorJiffies = currentProcessorJiffies;
}

string Process::Command() { return LinuxParser::Command(pid); }

string Process::Ram() { return LinuxParser::Ram(pid); }

string Process::User() { return LinuxParser::User(pid); }

long int Process::UpTime() { return LinuxParser::UpTime(pid); }

bool Process::operator<(const Process& other) const { 
    return this->cpuUtilization < other.cpuUtilization;
}
