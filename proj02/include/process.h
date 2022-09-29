#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include "linux_parser.h"

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process (int pid);
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  void CpuUtilization(long currActive, long currSystem);
  std::string Ram();
  long int UpTime();
  bool operator<(Process& a);

  // Declare any necessary private members
 private:
  int pid_; // initialized to invalid PID value
  float cpu_{0};
  long prevActive{0};
  long prevSystem{0};
};

#endif