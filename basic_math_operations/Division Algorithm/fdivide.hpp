#pragma once

// divides and outputs a repeating decimal

#include "divide.hpp"

std::string fdivide(std::string dividend, std::string divisor, int &r1,
                    int &r2) {
  // Get rid of spaces, leading signs, etc ...
  dividend = multiply(dividend, "1");
  divisor = multiply(divisor, "1");

  // still have to deal with negative division

  std::string multipleDividend = "1", multipleDivisor = "1";
  // Convert decimals to normal numbers
  while (decimal_point_exists(dividend)) {
    dividend = shift_decimal_point(dividend, 1);
    multipleDividend += "0";
  }

  while (decimal_point_exists(divisor)) {
    divisor = shift_decimal_point(divisor, 1);
    multipleDivisor += "0";
  }

  int decimalPointShift =
      -1 * ((int)(multipleDividend.length() - multipleDivisor.length()));

  std::string quotient;
  bool isInDecimals = false;

  std::string dividendDigits =
      multiply("1", dividend); // Remove redundant zeroes.
  dividend.clear();
  divisor = multiply("1", divisor); // Remove redundant zeroes.

  std::map<std::string, std::string> multiplicationTable;

  for (auto i = 0; i <= 10; i++) {
    multiplicationTable.insert(
        {std::to_string(i), multiply(std::to_string(i), divisor)});
  }

  std::map<std::string, int> previousRemainders;
  int currentDecimalPlace = 1;
  while (true) {
    if (dividendDigits.empty()) {
      dividend += "0";
      if (!isInDecimals) {
        quotient += ".";
        isInDecimals = true;
      }
    } else {
      dividend += dividendDigits.substr(0, 1);
      dividendDigits.erase(0, 1);
    }

    std::string partAns =
        quotientFinder(dividend, divisor, multiplicationTable);
    quotient += partAns;

    if (isInDecimals) {
      if (previousRemainders.count(dividend)) {
        r1 = previousRemainders[dividend];
        r2 = currentDecimalPlace;
        return quotient;
      } else
        previousRemainders.insert({dividend, currentDecimalPlace});
      currentDecimalPlace++;
    }

    dividend = subtract(dividend, (multiply(partAns, divisor)));
  }

  return shift_decimal_point(quotient,
                             decimalPointShift); // Remove redundant
                                                 // zeroes from back.
}