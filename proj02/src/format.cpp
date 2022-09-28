#include <string>

#include "format.h"

using std::string;
using std::to_string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  string strHH, strMM, strSS;
  int hrs, min, sec;
  
  // Compute hrs:min:sec
  hrs = seconds / 3600;     
  min = (seconds % 3600) / 60;
  sec = seconds - (hrs*3600) - (min*60);
  
  // Convert to string 00:00:00 format
  strHH = DoubleDigitString(hrs);
  strMM = DoubleDigitString(min);
  strSS = DoubleDigitString(sec);
  
  return strHH + ":" + strMM + ":" + strSS; 
}

string Format::DoubleDigitString(int value) {
  return (value < 10) ? "0"+to_string(value) : to_string(value);
}