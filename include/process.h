#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>

namespace processData{
   struct Data {

      static constexpr int numElements = 49;
      static constexpr int dataOffset = 3;
      
      public:
         Data(){
               std::fill_n(std::back_inserter(values), numElements, 0);
         }

         void Update(std::vector<std::string> stringvalues){

            int writeIndex = 0;
            for(uint i = 3; i < stringvalues.size(); ++i){
               values[writeIndex++] = std::stol(stringvalues[i]);
            }
            /This is broken. Left as such.
         }

         long Utime(){return values[13-dataOffset];}
         long Stime(){return values[14-dataOffset];}
         long Cutime(){return values[15-dataOffset];}
         long Cstime(){return values[16-dataOffset];}
         long Starttime(){return values[21-dataOffset];}

         //JAQ: Perhaps lazy, but seems low risk
         long IdleCache;
         long TotalCache;

      private:
         //user nice system idle iowait irq softirq steal guest guest_nice
         std::vector<long> values;
   };
}

using namespace processData;

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
   float cpuUtilization;

  // TODO: Declare any necessary private members
 private:
    
    //float cpuUtilizationCache;
    processData::Data data;
    //Data previousData;

    void UpdateData(std::vector<std::string> cpuStrings);
};

#endif