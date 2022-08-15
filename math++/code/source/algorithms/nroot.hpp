#pragma once

#include <chrono>
#include <string>

#include "../../../../basic_math_operations/basic_math_operations.hpp"

std::vector<int> turn_to_digits(const std::string &str_n) {
  std::vector<int> answer;
  for (auto i : str_n)
    answer.push_back(i - 48);
  return answer;
}

bool smaller_than_equal(const std::string &a1,
                        const std::string &b1) { // if a <= b return true;
  std::string a = a1;
  std::string b = b1;

  std::reverse(a.begin(), a.end());
  std::reverse(b.begin(), b.end());

  std::vector<int> a_vec = turn_to_digits(a);
  std::vector<int> b_vec = turn_to_digits(b);
  if (a.length() > b.length())
    for (auto i = 0; i < a.length() - b.length(); i++)
      b_vec.push_back(0);
  if (a.length() < b.length())
    for (auto i = 0; i < b.length() - a.length(); i++)
      a_vec.push_back(0);
  a_vec = reverse_vec(a_vec);
  b_vec = reverse_vec(b_vec);

  for (int i = 0; i < a_vec.size(); i++) {
    if (a_vec[i] > b_vec[i])
      return false;
    if (a_vec[i] < b_vec[i])
      return true;
  }

  return true;
}

#include "old/PrimeFactor/PrimeFactor.h"

std::string power(const std::string &a, long long b) {
  std::string answer = "1";
  for (auto i = 0; i < b; i++)
    answer = multiply(answer, a);
  return answer;
}

inline std::string absolute(std::string s) {
  return (s[0] == '-') ? s.substr(1, s.length()) : s;
}

std::string numerical_round(std::string number, int decimalPlaces) {
  if (!decimal_point_exists(number) ||
      number.length() - 1 - decimal_point_location(number) < decimalPlaces) {
    return number;
  }
  return number.substr(0, decimal_point_location(number)) +
         number.substr(decimal_point_location(number), decimalPlaces + 1);
}

std::string nroot(std::string number, std::string root,
                  long long numDecimalPlaces) {
  std::string answer = (numDecimalPlaces > 3) ? nroot(number, root, 3)
                                              : number; // decent approximation
  std::string prevAnswer = "lol"; // in honours of the great prakarsh
  long long i = 0;
  while (prevAnswer != answer) {
    auto start = std::chrono::high_resolution_clock::now();
    auto x =
        add(multiply((subtract(root, "1")), power(answer, std::stoll(root))),
            number);
    prevAnswer = answer;
    answer = divide(
        x, multiply(root, power(answer, std::stoll(subtract(root, "1")))),
        x.length() + 1);
    // round to prevent exp. time growth
    answer = numerical_round(answer, numDecimalPlaces);
    auto end = std::chrono::high_resolution_clock::now();

    if (i != 0) {
      std::cout << "\33[2K\r";
    }
    std::cout << "Run #" << i << ": " << answer << " ("
              << std::chrono::duration_cast<std::chrono::milliseconds>(end -
                                                                       start)
                         .count() /
                     1000.0
              << " s)" << std::flush;
    i++;
  }
  std::cout << "\33[2K\r";
  return answer;
}
