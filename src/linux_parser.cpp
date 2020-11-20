#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
//JAQ: This doesn't sound fun :D
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

//JAQ: Done
float LinuxParser::MemoryUtilization() {

  //string memTotal, memFree, memAvailable, Buffers;
  string line, key, value;

  float memTotal, memFree;

  //Stop a divide zero in case of some read error, and stop unnecessary IO.
  int foundDetails = 0;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      //std::replace(line.begin(), line.end(), ':', '');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal = std::stof(value); 
          foundDetails++;
        }
        if (key == "MemFree:") {
          memFree = std::stof(value); 
          foundDetails++;
        }

        if(foundDetails == 2){
          return memFree/memTotal;
        }
      }
    }
  }

  return 0;
}

//JAQ: Done
long LinuxParser::UpTime() { 
  
  string timeUp;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    
    std::getline(stream, line);
    std::replace(line.begin(), line.end(), '.', ' ');

    std::istringstream linestream(line);
    linestream >> timeUp;
  }
  long timeUpNum = std::stol(timeUp);

  return timeUpNum;
}

// JAQ: Done
vector<string> LinuxParser::CpuUtilization() { 
  string line, key, value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        
        if (key == "cpu") {

          //Does this optimise to useing move semantics because it's a rvalue?
          return vector<string>(std::istream_iterator<string>(linestream), {});
        }
      }
    }
  }
  
  return {}; 
  
}

// JAQ: Done
// JAQ: It's tempting to break out a method for this, RunningProcesses, and maybe CPUUtilisations. Probably not worth it for this number of uses.
// JAQ: Also tempting to cache the values somehow, but then would need state, which creates a whole mess. 
int LinuxParser::TotalProcesses() {
  
  string line, key, value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        
        if (key == "processes") {
 
          return std::stoi(value);
        }
      }
    }
  }
  
  return 0; 

}

// JAQ: Done
int LinuxParser::RunningProcesses() { 
  
  string line, key, value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        
        if (key == "procs_running") {
 
          return std::stoi(value);
        }
      }
    }
  }
  
  return 0; 
}

// JAQ: Done
vector<string> LinuxParser::CpuUtilization(int pid){

  string timeUp;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    
    std::getline(stream, line);
    std::istringstream linestream(line);

    return vector<string>(std::istream_iterator<string>(linestream), {});
  }

  return vector<string>{};
}

// JAQ: Done
string LinuxParser::Command(int pid) { 
  
  string timeUp;
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    
    std::getline(stream, line);
  }

  return line;
}

// JAQ: Done
string LinuxParser::Ram(int pid) { 
  
  string line, key, value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        
        if (key == "VmSize:") {

          //JAQ: OK, this is just kind of a fun way to do this rather than two casts and allocations
          int size = value.size();
          if(size >= 4){
            value.erase(size-3);
            return value;
          }

          return "0";
        }
      }
    }
  }

  return string(); 
}

// JAQ: Done
string LinuxParser::Uid(int pid) { 
  
  string line, key, value;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);

  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        
        if (key == "Uid:") {

          return value;
        }
      }
    }
  }

  return string();
}

// JAQ: Done
string LinuxParser::User(int pid){

  string uid = Uid(pid);

  if(uid.empty())
    return string();

  string line, pswdName, pswdPass, pswdUid;
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> pswdName >> pswdPass >> pswdUid) {
        if (pswdUid == uid) {

          return pswdName;
        }
      }
    }
  }
  return string();
  
}

// JAQ: Done
long LinuxParser::UpTime(int pid) { 
  
  string line, timeUp;

  std::ifstream stream(kProcDirectory + to_string(pid)+ kStatFilename);

  if (stream.is_open()) {
    
    std::getline(stream, line);
    std::istringstream linestream(line);

    for (int i=0; i < 21; i++) {
      linestream.ignore(256, ' ');    
    }
    linestream >> timeUp;

    return UpTime()-std::stol(timeUp)/sysconf(_SC_CLK_TCK);
  }
  
  return 0;
 }