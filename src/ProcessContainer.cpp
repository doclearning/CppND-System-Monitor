#include <vector>
#include <map>
#include <algorithm>

#include "ProcessContainer.h"
#include "process.h"

void ProcessContainer::Update(vector<int>& pids){

      for(int pid : pids){  

        //JAQ: Check if the pid exists in the map. Could do this in one line, but want to avoid creating pointer if possible
        if(processMap.find(pid) == processMap.end()){

            Process* process = new Process(pid);

            //Add to both containers
            processMap.emplace(pid, process);
            processVec.emplace_back(process);
        }

      }

      //JAQ TODO: Handle removal if a process disappears.
      //JAQ TODO: Probably want to iterate through everything and compare, and flag, then remove all and delete pointers
}

//JAQ: Lambda to support vector of pointers
void ProcessContainer::Sort(){

  std::sort(processVec.begin(), processVec.end(), [](const Process* processA, const Process* processB) {
    return processA->pid > processB->pid;
  });
}