#include <string>
//#include <chrono>

#include "format.h"

using std::string;

//JAQ: Done
string Format::ElapsedTime(long seconds) {
    int hh = seconds / 3600;
    int mm = (seconds % 3600) / 60;
    int ss = (seconds % 3600) % 60;
    
    //Could use sprintf to format a char array here, but didn't want to really deal with chars
    //Could use chrono, but looks really messy until C++20
    //A lot of allocations like this though. Hmmm....

    string formattedTime = std::to_string(hh) + ":" + std::to_string(mm) + ":" + std::to_string(ss);
    
    return formattedTime;
}