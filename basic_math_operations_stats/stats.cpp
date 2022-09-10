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

class result {
public:
  std::string numerator, denominator;
  std::string quotient, remainder;
  result(std::string n, std::string d, std::string q, std::string r) {
    numerator = n;
    denominator = d;
    quotient = q;
    remainder = r;
  }
  result() {
    quotient = "NaN";
    remainder = "NaN";
  }
};

int main() {
  std::vector<double> divideTimes;
  std::vector<result> results;
  for (auto i = 1; i <= 5000; i++) {
    std::cout << "Performing test " << i << ".\n";
    std::string numerator, denominator;
    for (auto j = 0; j < i; j++) {
      numerator.push_back(random_number(0, 9) + 48);
      denominator.push_back(random_number(0, 9) + 48);
    }

    while (std::string(i, '0') == denominator) {
      denominator.clear();
      for (auto j = 0; j < i; j++) {
        denominator.push_back(random_number(0, 9) + 48);
      }
    }

    std::string modulo;
    auto start = std::chrono::high_resolution_clock::now();
    std::string quotient = divide_whole(numerator, denominator, modulo);
    auto end = std::chrono::high_resolution_clock::now();
    divideTimes.push_back(
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count());
    results.emplace_back(numerator, denominator, quotient, modulo);
  }

//   int height = (int)std::floor(
//       *std::max_element(divideTimes.begin(), divideTimes.end()));
//   cimg_library::CImg<unsigned char> image(divideTimes.size() + 1, height + 1, 1,
//                                           3, 0);
//
//   for (auto i = 0; i < divideTimes.size(); i++) {
//     for (auto j = 0; j <= divideTimes[i]; j++) {
//       image(i, height - j, 0, 0) = 0;
//       image(i, height - j, 0, 1) = 255;
//       image(i, height - j, 0, 2) = 0;
//     }
//   }

  for (auto i = 0; i < divideTimes.size(); i++)
    std::cout << i + 1 << ": " << divideTimes[i] << '\n';

  // image.save("divideResults.bmp");
}
