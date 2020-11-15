#ifndef PROCESSOR_H
#define PROCESSOR_H

//user    nice   system  idle      iowait irq   softirq  steal  guest  guest_nice
struct Data {
    
    public:


    private:

    vector<int> data(10);

};

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    Data currentData, previousData;

    void UpdateData(vector<string> cpuStrings);

};

#endif