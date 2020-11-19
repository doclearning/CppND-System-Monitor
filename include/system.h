#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

#include "process.h"
#include "processor.h"
#include "processContainer.h"

class System {
 public:
  Processor& Cpu();                   
  std::vector<Process>& Processes();  
  float MemoryUtilization();          
  long UpTime();                      
  int TotalProcesses();               
  int RunningProcesses();             
  std::string Kernel();               
  std::string OperatingSystem();     

 
 private:
  Processor cpu_ = {};
  ProcessContainer processContainer = {};
};

#endif