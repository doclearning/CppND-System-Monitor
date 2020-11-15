#include <algorithm>

#include "processor.h"
#include "linux_parser.h"

using std::vector;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    
    //Called with move semantics as this is an rvalue?
    UpdateData(LinuxParser::CpuUtilization());
    
    

 }

 void Processor::UpdateData(vector<string> cpuStrings){

    for(auto item : cpuStrings){

        std::stol(item);
    }
 }