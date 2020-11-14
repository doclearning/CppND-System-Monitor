#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

//JAQ: Done
std::string System::Kernel() { return LinuxParser::Kernel(); }

//JAQ: Done
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

//JAQ: Done
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 5; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 10; }

//JAQ: Done
long int System::UpTime() { return LinuxParser::UpTime(); }