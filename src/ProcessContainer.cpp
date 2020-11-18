#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include "ProcessContainer.h"
#include "process.h"

void ProcessContainer::Update(vector<int>& pids){

  CleanUp(pids);

  for(int pid : pids){  

    //JAQ: Check if the pid exists in the set
    if(processIds.find(pid) == processIds.end()){

        //Add to both containers
        processVec.emplace_back(pid);
        processIds.insert(pid);
    }
  }


  long totalProcessorJiffies =  cpu_.TotalJiffies();

  for(auto& process : processVec){
    process.UpdateCpuUtilization(totalProcessorJiffies);
  }
}

//JAQ: There's probably a much better way to do this.
//JAQ: Firstly, the set/vector combo is just horrible. Needs a full rethink.
//JAQ: Secondly, there's probably a better way to remove from the vector, but I can't see how as the removal condition is a member variable. Probably a fancy lambda?
void ProcessContainer::CleanUp(vector<int>& pids){

  std::set<int> result;
  std::set_difference(processIds.begin(), processIds.end(), pids.begin(), pids.end(), std::inserter(result, result.end()));

  //processVec.erase(std::remove(processVec.begin(), processVec.end(), X), processVec.end());

  for(auto& toRemove: result){
    processIds.erase(toRemove);
    int idToRemove = -1;
    for(uint i = 0; i < processVec.size(); ++i){
      if(processVec[i].pid == toRemove){
        idToRemove = i;
        break;
      }
    }
    if(idToRemove >= 0)
      processVec.erase(processVec.begin()+idToRemove);
  }
}

void ProcessContainer::IsMissing(Process& candidate){

}

void ProcessContainer::Sort(){

  //std::sort(processVec.begin(), processVec.end()), std::greater<Process>());
  std::sort(processVec.begin(), processVec.end(),[] (Process const& a, Process const& b) { return a.cpuUtilization > b.cpuUtilization; });
}