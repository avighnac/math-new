#pragma once

#include <string>

#include <basic_math_operations.hpp>

std::string modulus(const std::string &a,
                    const std::string &b) { /*Takes two numbers as
                                              input and outputs their
                                              modulus.*/
  std::string answer;
  divide_whole(a, b, answer);
  return answer;
}