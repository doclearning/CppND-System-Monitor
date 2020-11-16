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

// JAQ: I can't see any reason to do any of this given how I've structured things.
// JAQ: Also doesn't seem to be a requirement in the project rubric.


// // TODO: Read and return the number of jiffies for the system
// long LinuxParser::Jiffies() { return 0; }

// // TODO: Read and return the number of active jiffies for a PID
// // REMOVE: [[maybe_unused]] once you define the function
// long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// // TODO: Read and return the number of active jiffies for the system
// long LinuxParser::ActiveJiffies() { return 0; }

// // TODO: Read and return the number of idle jiffies for the system
// long LinuxParser::IdleJiffies() { return 0; }

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
          return vector<string>(std::istream_iterator<string>(linestream), {});;
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

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }