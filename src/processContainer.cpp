#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include "processContainer.h"
#include "process.h"

using std::vector;

void ProcessContainer::Update(vector<int>& pids){

  CleanUp(pids);

  for(int pid : pids){  

    //JAQ: Add to containers if not present. Could potentially do a set_ operation here. Allocations but no loop...
    if(processIds.find(pid) == processIds.end()){

        //Add to both containers
        processVec.emplace_back(pid);
        processIds.insert(pid);
    }
  }

  //JAQ: Calc cpu usage, and send to process calculation
  long totalProcessorJiffies =  cpu_.TotalJiffies();

  for(auto& process : processVec){
    process.UpdateCpuUtilization(totalProcessorJiffies);
  }
}

//JAQ: Cleanup old processes. Somewhat proud of this. At least I now know what a capture list is :D
void ProcessContainer::CleanUp(vector<int>& pids){

  std::set<int> toRemove;
  std::set_difference(processIds.begin(), processIds.end(), pids.begin(), pids.end(), std::inserter(toRemove, toRemove.end()));

  processVec.erase(std::remove_if(processVec.begin(), processVec.end(),
                    [&toRemove](const Process& proc){ return toRemove.find(proc.pid) != toRemove.end(); }),
                    processVec.end());

}

void ProcessContainer::Sort(){

  //std::sort(processVec.begin(), processVec.end()), std::greater<>());
  std::sort(processVec.begin(), processVec.end(),[] (Process const& a, Process const& b) { return a.cpuUtilization > b.cpuUtilization; });
}