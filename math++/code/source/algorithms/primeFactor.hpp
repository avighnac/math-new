#pragma once

#include "Factorization/algebraic_number_class.hpp"
#include "modulus.hpp"
#include "old/PrimeFinder/isPrime.h"
#include <map>
#include <vector>

namespace prime_factor {
std::vector<algebraic_num::algebraic_number> prime_factor(std::string num) {

  if (algebraic_num::smaller_than(algebraic_num::algebraic_number(num),
                                  algebraic_num::algebraic_number("0"))) {
    auto answer = prime_factor(multiply(num, "-1"));
    answer.emplace_back("-1");
    return answer;
  }

  if (isPrime(num))
    return {algebraic_num::algebraic_number(num)};
  if (num == "1")
    return {algebraic_num::algebraic_number("1")};

  std::vector<algebraic_num::algebraic_number> primes;

  primes.emplace_back(algebraic_num::algebraic_number("2"));
  auto highest = primes[0];

  std::vector<algebraic_num::algebraic_number> answer;

  while (num != "1") {
    for (auto &i : primes) {
      std::string modulus;
      auto tempNum = divide_whole(num, i.constantPart, modulus);
      if (modulus == "0") {
        num = tempNum;
        answer.push_back(i);
      }
    }

    auto x = algebraic_num::algebraic_number(inc(highest.constantPart));
    bool incAmount =
        (!((x.constantPart[x.constantPart.length() - 1] - 48) & 1));
    while (!isPrime(x.constantPart)) {
      if (incAmount) {
        x = algebraic_num::algebraic_number(inc(x.constantPart));
        incAmount = false;
      } else
        x = algebraic_num::algebraic_number(inc(inc(x.constantPart)));
    }
    if (modulus(num, x.constantPart) == "0")
      primes.push_back(x);
    highest = x;
  }

  return answer;
}
} // namespace prime_factor
