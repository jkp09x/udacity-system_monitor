#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {}

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const { return cpu_; }

void Process::CpuUtilization(long currActive, long currSystem) {
  long active{currActive - prevActive};
  long system{currSystem - prevSystem};
  
  prevActive = currActive;
  prevSystem = currSystem;
  
  cpu_ = static_cast<float>(active) / system;
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(Pid()); }

// Overload the "greater than" comparison operator for Process objects
bool Process::operator>(const Process& a) const { 
  return CpuUtilization() > a.CpuUtilization(); 
}