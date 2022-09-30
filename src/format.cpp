#include <string>

#include "format.h"

using std::string;
using std::to_string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
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