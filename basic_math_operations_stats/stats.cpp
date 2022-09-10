#include "../basic_math_operations/basic_math_operations.hpp"
// #include "libs/CImg/CImg.h"
// #include "old_bmo.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

int random_number(int start, int end) {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(start, end);
  return (dist(rng));
}

#define print_res(name)                                                        \
  std::cout << "name: " << name << "\n";                                       \
  for (auto i = 0; i < times.size(); i++)                                      \
    std::cout << i + 1 << ": " << times[i] << '\n';                            \
  std::cout << "end\n";                                                        \
  times.clear();

int main() {
  std::cout << "Starting tests...\n";
  std::vector<double> times;
  for (auto i = 1; i <= 5000; i++) {
    std::string num1, num2;
    for (auto j = 0; j < i; j++) {
      num1.push_back(random_number(0, 9) + 48);
      num2.push_back(random_number(0, 9) + 48);
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string answer = add_whole(num1, num2);
    auto end = std::chrono::high_resolution_clock::now();
    times.push_back(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count());
  }
  print_res("add_whole");
  for (auto i = 1; i <= 5000; i++) {
    std::string num1, num2;
    for (auto j = 0; j < i; j++) {
      num1.push_back(random_number(0, 9) + 48);
      num2.push_back(random_number(0, 9) + 48);
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string answer = subtract_whole(num1, num2);
    auto end = std::chrono::high_resolution_clock::now();
    times.push_back(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count());
  }
  print_res("subtract_whole");
  for (auto i = 1; i <= 5000; i++) {
    std::string num1, num2;
    for (auto j = 0; j < i; j++) {
      num1.push_back(random_number(0, 9) + 48);
      num2.push_back(random_number(0, 9) + 48);
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::string answer = multiply_whole(num1, num2);
    auto end = std::chrono::high_resolution_clock::now();
    times.push_back(
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
            .count());
  }
  print_res("multiply_whole");
  for (auto i = 1; i <= 5000; i++) {
    std::string numerator, denominator;
    for (auto j = 0; j < i; j++) {
      numerator.push_back(random_number(0, 9) + 48);
      denominator.push_back(random_number(0, 9) + 48);
    }

    while (std::string(i, '0') == denominator) {
      denominator.clear();
      for (auto j = 0; j < i; j++)
        denominator.push_back(random_number(0, 9) + 48);
    }

    std::string modulo;
    auto start = std::chrono::high_resolution_clock::now();
    std::string quotient = divide_whole(numerator, denominator, modulo);
    auto end = std::chrono::high_resolution_clock::now();
    times.push_back(
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count());
  }
  print_res("divide_whole");
}
