#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include <string>
#include <iostream>

namespace processorData{
struct Data {

    static constexpr int numElements = 10;
    
    public:
        Data(){
            std::fill_n(std::back_inserter(values), numElements, 0);
        }

        void Update(std::vector<std::string> stringvalues){

            int index = 0;
            for(auto value : stringvalues){
                values[index++] = std::stol(value);
            }
        }

        long User(){return values[0];}
        long Nice(){return values[1];}
        long System(){return values[2];}
        long Idle(){return values[3];}
        long Iowait(){return values[4];}
        long Irq(){return values[5];}
        long SoftIrq(){return values[6];}
        long Steal(){return values[7];}
        long Guest(){return values[8];}
        long Guest_nice(){return values[9];}

        //JAQ: Perhaps lazy, but seems low risk
        long IdleCache;
        long TotalCache;

    private:
        //user nice system idle iowait irq softirq steal guest guest_nice
        std::vector<long> values;
};
}

using namespace processorData;

class Processor {
 public:
  float Utilization();

 private:
    processorData::Data currentData;
    processorData::Data previousData;

    void UpdateData(std::vector<std::string> cpuStrings);

};

#endif