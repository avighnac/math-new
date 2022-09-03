#pragma once

#include "../Subtraction Algorithm/subtract.hpp"
#include "../shift_decimal_point.hpp"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#ifndef _add_hpp_
#define _add_hpp_
#ifndef _str_contains_
#define _str_contains_
static bool str_contains(const std::string &str, char charac) {
  for (auto &i : str)
    if (i == charac)
      return true;
  return false;
}
#endif

#ifndef _digitize_
#define _digitize_
std::vector<int> digitize(std::string str_n) {
  std::vector<int> answer;
  for (int i = str_n.length() - 1; i > -1; i--) {
    answer.push_back(str_n[i] - 48);
  }
  return answer;
}
#endif

#ifndef _add_
#define _add_

#if defined(_WIN32)
static std::string add_whole(const std::string &a1, const std::string &b1) {
  std::string a = a1;
  std::string b = b1;
  if (a1 == "")
    a = "0";
  if (b1 == "")
    b = "0";

  std::vector<int> a_vec = digitize(a);
  std::vector<int> b_vec = digitize(b);
  if (a.length() > b.length())
    for (auto i = 0; i < a.length() - b.length(); i++)
      b_vec.push_back(0);
  if (a.length() < b.length())
    for (auto i = 0; i < b.length() - a.length(); i++)
      a_vec.push_back(0);

  std::vector<int> addition;
  for (auto i = 0; i < a_vec.size(); i++)
    addition.push_back(a_vec[i] + b_vec[i]); // Adding every digit of a and b

  for (auto i = 0; i < a_vec.size(); i++) {
    if (std::to_string(addition[i]).length() == 2 && i != a_vec.size() - 1) {
      int carry_forward = addition[i] / 10;
      addition[i + 1] += carry_forward;
      addition[i] -= carry_forward * 10;
    }
  }
  std::string answer;
  for (int i = addition.size() - 1; i > -1; i--)
    answer += std::to_string(addition[i]); // Re-Reversing the array

  return answer;
}
#else
extern "C" void _add_whole(const char *a, const char *b, char *res);
static std::string add_whole(const std::string &a1, const std::string &b1) {
  char *a = (char *)malloc(a1.length() + 1);
  strcpy(a, a1.c_str());
  char *b = (char *)malloc(b1.length() + 1);
  strcpy(b, b1.c_str());
  char *res = (char *)malloc(std::max(a1.length(), b1.length()) + 5);
  _add_whole(a, b, res);
  std::string answer(res);
  free(a);
  free(b);
  free(res);
  return answer;
}
#endif

std::string add(std::string a, std::string b) {
  if (a.empty())
    a = "0";
  if (b.empty())
    b = "0";
  if (a[0] == '+')
    a = a.substr(1, a.length());
  if (b[0] == '+')
    b = b.substr(1, b.length());

  if ((a[0] != '-' && b[0] == '-') || (a[0] == '-' && b[0] == '-')) {
    return subtract(a, b.substr(1, b.length()));
  }
  if (a[0] == '-' && b[0] != '-') {
    return subtract(b, a.substr(1, a.length()));
  }

  if (!(str_contains(a, '.') || str_contains(b, '.'))) {
    return add_whole(a, b);
  } else {
    if (!decimal_point_exists(a))
      a += ".0";
    if (!decimal_point_exists(b))
      b += ".0";
    if (a[1] == '.')
      a = "0" + a;
    if (b[1] == '.')
      b = "0" + b;
    size_t a_dec_loc = decimal_point_location(a);
    size_t b_dec_loc = decimal_point_location(b);

    // We want to make sure digits before and after decimal are equal
    size_t a_digits_after_decimal =
        a.substr(a_dec_loc + 1, a.length()).length();
    size_t b_digits_after_decimal =
        b.substr(b_dec_loc + 1, b.length()).length();
    while (a_digits_after_decimal != b_digits_after_decimal) {
      if (a_digits_after_decimal > b_digits_after_decimal) {
        b_digits_after_decimal++;
        b += "0";
      }
      if (a_digits_after_decimal < b_digits_after_decimal) {
        a_digits_after_decimal++;
        a += "0";
      }
    }

    if (a.length() > b.length())
      for (auto i = 0; i < a.length() - b.length(); i++) {
        b = "0" + b;
        b_dec_loc++;
      }
    if (a.length() < b.length())
      for (auto i = 0; i < b.length() - a.length(); i++) {
        a = "0" + a;
        a_dec_loc++;
      }

    const size_t n_to_shift = a.substr(a_dec_loc + 1, a.length()).length();
    a.erase(a_dec_loc, 1);
    b.erase(b_dec_loc, 1);
    return shift_decimal_point(add_whole(a, b), -1 * n_to_shift);
  }
}
#endif
#endif