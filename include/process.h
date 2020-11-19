#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <iostream>


struct ProcessData {

   static constexpr int numElements = 5;
   
   public:

      void Update(std::vector<std::string> valuesIn){

         utime = std::stol(valuesIn[13]);
         stime = std::stol(valuesIn[14]);
         cutime = std::stol(valuesIn[15]);
         cstime = std::stol(valuesIn[16]);
         starttime = std::stol(valuesIn[21]);
      }

      long Utime(){return utime;}
      long Stime(){return stime;}
      long Cutime(){return cutime;}
      long Cstime(){return cstime;}
      long Starttime(){return starttime;}


   private:

      long utime, stime, cutime, cstime, starttime = 0;
};

class Process {
 public:
    Process() {}
    Process(int pidIn) : pid(pidIn){}

    int Pid();                               
    std::string User();                      
    std::string Command();                   
    float CpuUtilization();                  
    std::string Ram();                       
    long int UpTime();                       
    bool operator<(const Process&  other) const; 

   int pid = 0;
   float cpuUtilization = 0;

   void UpdateCpuUtilization(long totalProcessorJiffies);

 private:
    
    ProcessData data;

    bool hasPreviousData = false;

   long previousProcessorJiffies = 0;
   long previousProcessJiffies = 0;

    void UpdateData(std::vector<std::string> cpuStrings);
};

#endif