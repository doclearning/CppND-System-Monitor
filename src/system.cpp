#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// JAQ: Done
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process*>& System::Processes() { 
    
    vector<int> pids{LinuxParser::Pids()};

    processContainer.Update(pids);
    processContainer.Sort();

    return processContainer.processVec;
}

//JAQ: Done
std::string System::Kernel() { return LinuxParser::Kernel(); }

//JAQ: Done
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

//JAQ: Done
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// JAQ: Done
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// JAQ: Done
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

//JAQ: Done
long int System::UpTime() { return LinuxParser::UpTime(); }