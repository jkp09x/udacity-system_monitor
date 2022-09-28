#include "processor.h"

// Return the aggregate CPU utilization
float Processor::Utilization() {
  std::vector<std::string> cpuTimes = LinuxParser::CpuUtilization();
  std::vector<long> cpuValues;

  // Lambda function to convert vector<string> to vector<long>
  std::transform(cpuTimes.begin(), cpuTimes.end(), std::back_inserter(cpuValues),[](const std::string& str) { return std::stol(str); });
  
  idle_ = cpuValues[LinuxParser::kIdle_] + cpuValues[LinuxParser::kIOwait_];
  
  totaltime_ = cpuValues[LinuxParser::kUser_] + cpuValues[LinuxParser::kNice_]
               + cpuValues[LinuxParser::kSystem_] + cpuValues[LinuxParser::kIdle_]
               + cpuValues[LinuxParser::kIOwait_] + cpuValues[LinuxParser::kIRQ_]
               + cpuValues[LinuxParser::kSoftIRQ_] + cpuValues[LinuxParser::kSteal_];
  
  // returning CPU Usage Percentage
  return (totaltime_ - idle_) / totaltime_; 
}