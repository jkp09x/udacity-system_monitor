#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  vector<int> pids{LinuxParser::Pids()};
  
  set<int> uniquePids;
  for (Process& process : processes_) {
    uniquePids.insert(process.Pid());
  }
  
  for (auto pid : pids) {
    // Add key to list if not found
    if (uniquePids.find(pid) == uniquePids.end())
      processes_.emplace_back(pid);
  }
  
  // Update CPU utilization
  for (auto& proc : processes_) {
    proc.CpuUtilization(LinuxParser::ActiveJiffies(proc.Pid()), LinuxParser::Jiffies());
  }
  
  std::sort(processes_.begin(), processes_.end(), std::greater<Process>());
  
  return processes_;
}

// Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel(); }

// Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// Return the number of seconds since the system started running
long System::UpTime() { return LinuxParser::UpTime(); }

