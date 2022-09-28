#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  /*
  // Guest time is already accounted in usertime
  usertime = usertime - guest;                             # As you see here, it subtracts guest from user time
  nicetime = nicetime - guestnice;                         # and guest_nice from nice time
  // Fields existing on kernels >= 2.6
  // (and RHEL's patched kernel 2.4...)
  unsigned long long int idlealltime = idletime + ioWait;  # ioWait is added in the idleTime
  unsigned long long int systemalltime = systemtime + irq + softIrq;
  unsigned long long int virtalltime = guest + guestnice;
  unsigned long long int totaltime = usertime + nicetime + systemalltime + idlealltime + steal + virtalltime;
  */
  //   unsigned long long int user_, nice_, system_, idle_, iowait_, irq_, softirq_, steal_, guest_, guest_nice_;
  user_ -= guest_;
  nice_ -= guest_nice_;
  
  idle_ += iowait_;
  system_ += irq_ + softirq_;
  totaltime_ = user_ + nice_ + system_ + idle_ + steal_ + guest_ + guest_nice_;
  
  // returning CPU Percentage  
  return user_; 
}