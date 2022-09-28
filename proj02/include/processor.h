#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  /* TODO: Bonus
  You might want to update the system monitor to report the current utilization of the processor, rather than the long-term average utilization since boot. 
  You would need to measure the difference in system utilization between two points in time relatively close to the present. A formula like:
      Δ active time units / Δ total time units
  Consider this a bonus challenge that is not required to pass the project
  */
  // Numbers in the /proc/stat cpu file
  unsigned long long int user_, nice_, system_, idle_, iowait_, irq_, softirq_, steal_, guest_, guest_nice_, totaltime_;
  float cpuUtilization_;
};

#endif