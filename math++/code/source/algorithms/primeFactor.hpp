#pragma once

#include "../math++/code/source/algorithms/Factorization/algebric_number_class.hpp"
#include "../math++/code/source/algorithms/modulus.hpp"
#include "../math++/code/source/algorithms/old/PrimeFinder/isPrime.h"
#include <vector>
#include <map>

namespace prime_factor {
std::vector<algebric_num::algebric_number> prime_factor(std::string num) {
  if (isPrime(num))
    return { algebric_num::algebric_number(num) };
  if (num == "1")
    return {algebric_num::algebric_number("1")};

  std::vector<algebric_num::algebric_number> primes;

  primes.emplace_back(algebric_num::algebric_number("2"));
  auto highest = primes[0];

  std::vector<algebric_num::algebric_number> answer;

  while (num != "1") {
    for (auto &i : primes) {
      std::string modulus;
      auto tempNum = divide_whole(num, i.constantPart, modulus);
      if (modulus == "0") {
        num = tempNum;
        answer.push_back(i);
      }
    }

    auto x = algebric_num::algebric_number(add(highest.constantPart, "1"));
    while (!isPrime(x.constantPart))
      x = algebric_num::algebric_number(add(x.constantPart, "1"));
    if (modulus(num, x.constantPart) == "0")
      primes.push_back(x);
    highest = x;
  }

  return answer;
}
} // namespace prime_factor