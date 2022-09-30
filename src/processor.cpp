#include "processor.h"

// Return the aggregate CPU utilization
float Processor::Utilization() {
  const long activeJiffies = LinuxParser::ActiveJiffies();
  const long idleJiffies = LinuxParser::IdleJiffies();
  
  long deltaActive{activeJiffies - prevActiveJiffies};
  long deltaIdle{idleJiffies - prevIdleJiffies};
  long deltaTotal{deltaActive + deltaIdle};
  
  prevActiveJiffies = activeJiffies;
  prevIdleJiffies = idleJiffies;
    
  return static_cast<float>(deltaActive) / deltaTotal;
}