#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
    Process(int pidIn) : pid(pidIn) {}
    Process() : pid(0) {}

    int Pid();                               
    std::string User();                      // TODO: See src/process.cpp
    std::string Command();                   // TODO: See src/process.cpp
    float CpuUtilization();                  // TODO: See src/process.cpp
    std::string Ram();                       // TODO: See src/process.cpp
    long int UpTime();                       // TODO: See src/process.cpp
    //bool operator<(Process const& a) const;  // JAQ: Sort instead done in ProcessContainer. Doesn't require this operator
    //bool operator>(Process const& a) const;
   const int pid = 0;

  // TODO: Declare any necessary private members
 private:
    
    float cpuUtilizationCache;
};

#endif