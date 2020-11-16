#ifndef PROCESSCONTAINER_H
#define PROCESSCONTAINER_H

#include <string>
#include <vector>
#include <map>

#include "process.h"

using std::vector;

class ProcessContainer {
 public:

   void Update(vector<int>& pids);
   void Sort();

   //JAQ TODO: This probably shouldnt't be accessible. Accessor returning a const? Can I do that?
    std::vector<Process*> processVec = {};

 private:
  
  std::map<int, Process*> processMap = {};
};

#endif