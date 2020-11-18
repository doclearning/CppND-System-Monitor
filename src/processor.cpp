#include <algorithm>

#include "processor.h"
#include "linux_parser.h"

using std::vector;
using std::string;
using namespace processorData;

// JAQ: Return the aggregate CPU utilization
// JAQ: uses cashing to reduve the number of calculations
float Processor::Utilization() {
    
    //JAQ: Called with move semantics as this is an rvalue
    //JAQ: Otheriwise should pass reference
    UpdateData(LinuxParser::CpuUtilization());
    
    //JAQ: Better to return as reference?
    currentData.IdleCache = currentData.Idle() + currentData.Iowait();
    long nonIdle = currentData.User() + currentData.Nice() + currentData.System() + currentData.Irq() + currentData.SoftIrq() + currentData.Steal();
    currentData.TotalCache = currentData.IdleCache + nonIdle;

    //JAQ: Store in a float now rather than casting later
    float totald = currentData.TotalCache - previousData.TotalCache;
    float idled = currentData.IdleCache - previousData.IdleCache;

    return (totald - idled)/totald;
 }

 long Processor::TotalJiffies() {
    
   currentData.Update(LinuxParser::CpuUtilization());

   //std::cout << " CPU(" << data << ") ";

   return currentData.GetAllSum();
 }

 void Processor::UpdateData(vector<string> cpuStrings){

    //JAQ: Essentially using a double buffer
    std::swap(currentData, previousData);
    currentData.Update(cpuStrings);
 }