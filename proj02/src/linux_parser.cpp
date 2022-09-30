#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "linux_parser.h"

using std::stof;
using std::stol;
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

// Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  float memTotal, memFree;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") {
          memTotal = stof(value);
        }
        if (key == "MemFree:") {
          memFree = stof(value);
        }
      }
    }
    return (memTotal - memFree) / memTotal;
  }
  
  // return default value
  return 0.0;
}

// Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string t1;

  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    if (linestream >> t1)
      return std::stoi(t1);
  }
  
  // return default value
  return 0.0;
}

// Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return UpTime() * sysconf(_SC_CLK_TCK); }

// Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) { 
  string line, key;
  
  vector<string> values;
  
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    while (linestream >> key) {
      values.push_back(key);
    }
  }
  
  if (values.size() > 21) {
    // 13 - user
    // 14 - kernel
    // 15 - child_user
    // 16 - child_kernel
    return stol(values[13]) + stol(values[14]) + stol(values[15]) + stol(values[16]);
  }
  
  return 0;
}

// Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  std::vector<std::string> cpuTimes = CpuUtilization();
  std::vector<long> cpuValues;

  // Lambda function to convert vector<string> to vector<long>
  std::transform(cpuTimes.begin(), cpuTimes.end(), std::back_inserter(cpuValues),[](const std::string& str) { return std::stol(str); });
  
  return (cpuValues[LinuxParser::kUser_] + cpuValues[LinuxParser::kNice_]
         + cpuValues[LinuxParser::kSystem_] + cpuValues[LinuxParser::kIdle_]
         + cpuValues[LinuxParser::kIOwait_] + cpuValues[LinuxParser::kIRQ_]
         + cpuValues[LinuxParser::kSoftIRQ_] + cpuValues[LinuxParser::kSteal_]);
}

// Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  std::vector<std::string> cpuTimes = CpuUtilization();
  std::vector<long> cpuValues;

  // Lambda function to convert vector<string> to vector<long>
  std::transform(cpuTimes.begin(), cpuTimes.end(), std::back_inserter(cpuValues),[](const std::string& str) { return std::stol(str); });
  
  return (cpuValues[LinuxParser::kIdle_] + cpuValues[LinuxParser::kIOwait_]);
}

// Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string key;
  string value;
  std::vector<string> cpuTimes;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == "cpu") {
          while (linestream >> value) { 
            cpuTimes.push_back(value); 
          }
          return cpuTimes;
        }
      }
    }
  }
  
  // return default value
  return cpuTimes;
}

// Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  int totalProcs;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          totalProcs = stof(value);
          return totalProcs;
        }
      }
    }
  }
  
  // return default value
  return totalProcs;
}

// Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  int procsRunning;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          procsRunning = stof(value);
          return procsRunning;
        }
      }
    }
  }
  
  return procsRunning;
}

// Read and return the command associated with a process
string LinuxParser::Command(int pid) { 
  string line;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    return line;
  }
  
  return string();
}

// Read and return the memory used by a process
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          return to_string(stoi(value) / 1024);
        }
      }
    }
  }

  return "";
}

// Read and return the user ID associated with a process
string LinuxParser::Uid(int pid) { 
  string line;
  string uid;
  string uidValue;
  
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> uid >> uidValue) {
        if (uid == "Uid:") {
          return uidValue;
        }
      }
    }
  }

  return string();
}

// Read and return the user associated with a process
string LinuxParser::User(int pid) { 
  string line;
  string value;
  
  std::ifstream filestream(kPasswordPath);
  
  if (filestream.is_open()) {
    value = "x:" + LinuxParser::Uid(pid);
    while (std::getline(filestream, line)) {
      if (line.find(value) != string::npos) {
        return line.substr(0, line.find(value) - 1);
      }
    }
  }
  return "";
}

// Read and return the uptime of a process
long int LinuxParser::UpTime(int pid) { 
  string line;
  string value;
  
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      int i = 0;
      while (linestream >> value) {
        if (i == 14) {
          return static_cast<long int>(stof(value) / sysconf(_SC_CLK_TCK));
        }
        ++i;
      }
    }
  }
  
  return 0.0;
}