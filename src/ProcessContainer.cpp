#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include "ProcessContainer.h"
#include "process.h"

void ProcessContainer::Update(vector<int>& pids){

      for(int pid : pids){  

        //JAQ: Check if the pid exists in the set
        if(processIds.find(pid) == processIds.end()){

            //Add to both containers
            processVec.emplace_back(pid);
            processIds.insert(pid);
        }
      }

      float updatedUtilization =  cpu_.TotalUtilization();

      for(auto process : processVec){
        //process.TotalProcessorUtilization = updatedUtilization;
        process.UpdateCpuUtilization(updatedUtilization);
      }

      //JAQ TODO: Handle removal if a process disappears.
      //JAQ TODO: Probably want to iterate through everything and compare, and flag, then remove all and delete pointers
}

void ProcessContainer::Sort(){

  //std::cout
  //std::sort(processVec.begin(), processVec.end());//, std::greater<>);
}

//JAQ: Lambda to support vector of pointers
// void ProcessContainer::Sort(){

//   std::sort(processVec.begin(), processVec.end(), [](const Process processA, const Process processB) {
//     return processA.cpuUtilization > processB.cpuUtilization;
//   });
// }