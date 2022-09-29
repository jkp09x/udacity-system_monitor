#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>
#include "linux_parser.h"

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

 private:
  float idle_, totaltime_;
};

#endif