#pragma once

#include "../Addition Algorithm/add.hpp"
#include "../Multiplication Algorithm/multiply.hpp"
#include "../Subtraction Algorithm/subtract.hpp"
#include "compare_string.hpp"
#include <string>

static std::string remove_leading_zeroes(std::string str) {
  str.erase(0, std::min(str.find_first_not_of('0'), str.size() - 1));
  return str;
}

static std::string
quotientFinder(std::string dividend,
               std::string divisor) { /*find highest number such that a*x <= b
                                         with a and b provided*/

  std::string x = "0";        // Declaring x variable (from line 14 (a*x <= b))
  std::string xPrevious = ""; /* x_previous tracks the previous value of x
                                    and terminates loop when they are equal the
                                  answer has been reached.*/

  while (xPrevious != x) {
    xPrevious = x; // Simply setting x_previous
    if (compare_string(dividend, (multiply(divisor, x))) ||
        remove_leading_zeroes(dividend) == (multiply(divisor, x))) { /*

100 (dividend) / 10 (divisor) = 10 (quotient)
if dividend > divisor * x, x will be incremented.
For example:
100 > 10 * 0 ∴ x++
100 > 10 * 1 ∴ x++
100 > 10 * 2 ∴ x++
...
100 > 10 * 9 ∴ x++
100 > 10 * 10 is FALSE and x is not incremented. x previous will be equal to x
now and the loop will break.
*/
      x = add(x, "1");
    }
  }

  return subtract(
      x,
      "1"); // Finally, return x - 1 because x starts off as 1 at declaration.
}

std::string divide(std::string dividend, std::string divisor,
                   std::string &modulusOut) {

  std::string quotient; // Declaring quotient variable to push answer into.

  std::string dividendDigits =
      dividend; // String to keep track of digits in dividend
  const size_t dividendLength = dividendDigits.length();
  dividend.clear();

  for (int i = 0; i < dividendLength; i++) {

    dividend += dividendDigits.substr(0, 1);
    dividendDigits.erase(0, 1);

    std::string partAns = quotientFinder(
        dividend, divisor); // Find the quotient to only the particular part it
                            // has worked on. (Refer to code on top).
    quotient += partAns;
    dividend = subtract(dividend, (multiply(partAns, divisor)));
    modulusOut = dividend;
  }

  return remove_leading_zeroes(quotient);
}

std::string divide(std::string dividend, std::string divisor) {
  std::string modulus;
  return divide(dividend, divisor, modulus);
}