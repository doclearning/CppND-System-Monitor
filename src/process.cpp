#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

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

    

    UpdateData(LinuxParser::CpuUtilization(pid));
    long uptime = LinuxParser::UpTime();

    long totalTime = data.Utime() + data.Stime(); //Consider adding child process time

    std::cout << "Totaltime("<< totalTime << ")\n";

    long hertz = sysconf(_SC_CLK_TCK);

    long seconds = uptime - (data.Starttime()/hertz);
    
    cpuUtilization = 100 * ((totalTime/(float)hertz)/(float)seconds);

    //std::cout << "Utiliz("<< cpuUtilization << ")\n";
    
    return cpuUtilization;
}

 void Process::UpdateData(vector<string> cpuStrings){

    //std::cout << "cpustrings(" << cpuStrings.size() << ")\n";
    //std::swap(currentData, previousData);
    data.Update(cpuStrings);
 }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; 
//}