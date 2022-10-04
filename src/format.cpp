#include <string>

#include "format.h"

using std::string;
using std::to_string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) { 
  string strHH, strMM, strSS;
  int hrs, min, sec;
  const int SECS_IN_MIN{60};
  const int MINS_IN_HR{60};
  const int SECS_IN_HR{SECS_IN_MIN * MINS_IN_HR};
  
  // Compute hrs:min:sec
  hrs = seconds / SECS_IN_HR;     
  min = (seconds % SECS_IN_HR) / MINS_IN_HR;
  sec = seconds - (hrs * SECS_IN_HR) - (min * MINS_IN_HR);
  
  // Convert to string 00:00:00 format
  strHH = DoubleDigitString(hrs);
  strMM = DoubleDigitString(min);
  strSS = DoubleDigitString(sec);
  
  return strHH + ":" + strMM + ":" + strSS; 
}

string Format::DoubleDigitString(int value) {
  return (value < 10) ? "0"+to_string(value) : to_string(value);
}