#pragma once

#include <string>

#include "Division Algorithm/divide.hpp"

std::string modulus(const std::string &a,
                    const std::string &b) { /*Takes two numbers as
                                              input and outputs their
                                              modulus.*/
  std::string answer;
  divide_whole(a, b, answer);
  return answer;
}