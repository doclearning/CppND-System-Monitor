#include <algorithm>

#include "processor.h"
#include "linux_parser.h"


using std::vector;
using std::string;

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    
    //Called with move semantics as this is an rvalue
    //Otheriwise should pass reference
    UpdateData(LinuxParser::CpuUtilization());
    
    //Do I need to return these as references?
    //JAQ TODO: odo cache new values in data, and then use prev values from data
    long prevIdle = previousData.Idle() + previousData.Iowait();
    long idle = currentData.Idle() + currentData.Iowait();
    
    long prevNonIdle = previousData.User() + previousData.Nice() + previousData.System() + previousData.Irq() + previousData.SoftIrq() + previousData.Steal();
    long nonIdle = currentData.User() + currentData.Nice() + currentData.System() + currentData.Irq() + currentData.SoftIrq() + currentData.Steal();

    long prevTotal = prevIdle + prevNonIdle;
    long total = idle + nonIdle;

    //Store in a float now rather than casting later
    float totald = total - prevTotal;
    float idled = idle - prevIdle;

    return (totald - idled)/totald;
 }

 void Processor::UpdateData(vector<string> cpuStrings){

    //Essentially using a double buffer
    std::swap(currentData, previousData);
    currentData.Update(cpuStrings);
 }