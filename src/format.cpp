#include <string>
//#include <chrono>

#include "format.h"

using std::string;

//JAQ: Done
string Format::ElapsedTime(long seconds) {
    int hh = seconds / 3600;
    int mm = (seconds % 3600) / 60;
    int ss = (seconds % 3600) % 60;

    char timestring[9];
    sprintf(timestring, "%02d:%02d:%02d", hh,mm,ss);
    return string(timestring);

    //Could use chrono, but looks really messy until C++20
}