#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <iostream>

namespace processData{
   struct Data {

      static constexpr int numElements = 5;
      
      public:
         Data(){
               //Wstd::fill_n(std::back_inserter(values), numElements, 0W);
         }

         void Update(std::vector<std::string> valuesIn){


            //std::cout << "size_hpp(" << stringvalues.size() << ")\n"
            //values = stringvalues;

            //std::swap(values, stringvalues);

            //int writeIndex = 0;
            // for(uint i = 0; i < stringvalues.size(); ++i){

            //    //std::cout << "(" << writeIndex << "," << stringvalues[i] << ") "
            //    if(i >= 3)values[i] = stringvalues[i]);
            //    else values[i] = 0;
            // }
            //std::cout << "\n";
            utime = std::stol(valuesIn[13]);
            stime = std::stol(valuesIn[14]);
            cutime = std::stol(valuesIn[15]);
            cstime = std::stol(valuesIn[16]);
            starttime = std::stol(valuesIn[21]);
         }

         long Utime(){return utime;}
         long Stime(){return stime;}
         long Cutime(){return stime;}
         long Cstime(){return stime;}
         long Starttime(){return stime;}

         //JAQ: Perhaps lazy, but seems low risk
         //long IdleCache;
         long TotalProcessCache;
         long TotalProcessorCache;

      private:
         //user nice system idle iowait irq softirq steal guest guest_nice
         //std::vector<std::string> values;
         long utime, stime, cutime, cstime, starttime = 0;
   };
}

using namespace processData;

class Process {
 public:
    Process(int pidIn/*, Processor& cpuIn*/) : pid(pidIn)/*, cpu(cpuIn)*/ {}
    //Process() : pid(0) {}

    int Pid();                               
    std::string User();                      
    std::string Command();                   
    float CpuUtilization();                  
    std::string Ram();                       
    long int UpTime();                       
    bool operator<(Process const& a) const;  
    //bool operator>(Process const& a) const;
   const int pid = 0;
   float cpuUtilization = 0;

   void UpdateCpuUtilization(float TotalProcessorUtilization);

 private:
    
    //float cpuUtilizationCache;
    processData::Data currentData;
    processData::Data previousData;

    bool hasPreviousData = false;

    void UpdateData(std::vector<std::string> cpuStrings);
};

#endif