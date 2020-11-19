#ifndef PROCESSCONTAINER_H
#define PROCESSCONTAINER_H

#include <string>
#include <vector>
#include <set>

#include "process.h"
#include "processor.h"

class ProcessContainer {
 public:

  void Update(std::vector<int>& pids);
  void Sort();

  std::vector<Process>& Processes(){
    return processVec;
  }

 private:
  Processor cpu_ = {};
  std::set<int> processIds;
  std::vector<Process> processVec = {};

  void CleanUp(std::vector<int>& pids);
  
};

#endif