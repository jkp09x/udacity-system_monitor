#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

 private:
  /* TODO: Bonus
  You might want to update the system monitor to report the current utilization of the processor, rather than the long-term average utilization since boot. 
  You would need to measure the difference in system utilization between two points in time relatively close to the present. A formula like:
      Δ active time units / Δ total time units
  Consider this a bonus challenge that is not required to pass the project
  */

  float idle_, totaltime_;
};

#endif