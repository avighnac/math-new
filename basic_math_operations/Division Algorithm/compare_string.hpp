#include "../Subtraction Algorithm/subtract.hpp"
#include <iostream>

#ifndef _compare_string_
#define _compare_string_

bool compare_string(std::string a, std::string b) {
  /*returns true if a > b*/
  return ((subtract(b, a))[0] == '-');
}

#endif