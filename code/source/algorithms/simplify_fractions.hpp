#include <string>

#include "Division Algorithm/divide.hpp"
#include "gcd.hpp"

std::pair<long long, long long>
fraction_simplifier(const std::pair<long long, long long> &fraction) {
  long long hcf = gcd(fraction.first, fraction.second);
  return {fraction.first / hcf, fraction.second / hcf};
}

std::pair<std::string, std::string>
fraction_simplifier(const std::pair<std::string, std::string> &fraction) {
  std::string hcf = gcd(fraction.first, fraction.second);
  return {divide_whole(fraction.first, hcf),
          divide_whole(fraction.second, hcf)};
}