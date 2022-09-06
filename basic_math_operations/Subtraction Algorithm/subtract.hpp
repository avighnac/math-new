#pragma once

#include "../shift_decimal_point.hpp"
#include "add_copy.hpp"
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#ifndef _subtract_
#define _subtract_
#ifndef _str_contains_
#define _str_contains_
static bool str_contains(const std::string &str, char charac) {
  return str.find(charac) != std::string::npos;
}
#endif

std::vector<int> split_into_digits(std::string str) {
  std::vector<int> answer;
  for (auto i : str)
    answer.push_back(i - 48);
  return answer;
}

std::vector<int> reverse_vec(std::vector<int> vec) {
  std::reverse(vec.begin(), vec.end());
  return vec;
}
#ifndef _reverse_string_
#define _reverse_string_
std::string reverse_string(std::string str) {
  std::reverse(str.begin(), str.end());
  return str;
}
#endif

static void remove_leading_zeroes_inplace(std::string &s) {
  if (const auto it = s.find_first_not_of('0') /*; it != 0*/) {
    if (it == std::string::npos)
      s = "0";
    else
      s.erase(0, it);
  }
}

static char sub_with_borrow(int aval, const int bval, bool &borrow) {
  if (borrow) {
    borrow = false;
    aval -= 1;
  }

  if (aval < bval) {
    borrow = true;
    aval += 10;
  }

  const int diff = aval - bval;
  return char(diff + '0');
}

static void reverse_in_place(std::string &s) {
  const size_t size = s.size();
  if (size < 2)
    return;
  for (size_t i = 0, j = size - 1; i < j; ++i, --j)
    std::swap(s[i], s[j]);
}

#if defined(_WIN32)
std::string subtract_whole(std::string a, std::string b) {
  if (a.empty())
    a = "0";
  if (b.empty())
    b = "0";
  if (a[0] == '+')
    a = a.substr(1, a.length());
  if (b[0] == '+')
    b = b.substr(1, b.length());
  if (a[0] != '-')
    a = "+" + a;
  if (b[0] != '-')
    b = "+" + b;

  if (a[0] == '-') {
    if (b[0] != '-') {
      return "-" + add_copy(a.substr(1, a.length()), b.substr(1, b.length()));
    }
    if (b[0] == '-') {
      std::string a_copy = a;
      a = b.substr(1, b.length());
      b = a_copy.substr(1, a.length());
    }
  }
  if (b[0] == '-' && a[0] != '-') {
    return add_copy(a.substr(1, a.length()), b.substr(1, b.length()));
  }
  if (a[0] == '+' && b[0] == '+') {
    a = a.substr(1, a.length());
    b = b.substr(1, b.length());
  }
  std::string a1 = a;
  std::string b1 = b;

  remove_leading_zeroes_inplace(a);
  remove_leading_zeroes_inplace(b);
  reverse_in_place(a);
  reverse_in_place(b);

  const auto asize = a.size();
  const auto bsize = b.size();
  const auto max_size = std::max(asize, bsize);

  std::string result;
  bool borrow = false;
  result.clear();
  result.append(max_size, '0');
  for (size_t i = 0; i < max_size; ++i) {
    const int aval = (i < asize) ? int(a.at(i) - '0') : 0;
    const int bval = (i < bsize) ? int(b.at(i) - '0') : 0;
    result.at(i) = sub_with_borrow(aval, bval, borrow);
  }

  if (borrow)
    return "-" + subtract_whole(b1, a1);

  reverse_in_place(result);
  remove_leading_zeroes_inplace(result);
  return result;
}
#else
extern "C" void _subtract_whole_same_length(const char *a, const char *b,
                                            char *res);
extern "C" void _subtract_whole(const char *a, const char *b, char *res);
std::string subtract_whole(std::string a, std::string b) {
  if (a.empty())
    a = "0";
  if (b.empty())
    b = "0";
  if (a[0] == '+')
    a = a.substr(1, a.length());
  if (b[0] == '+')
    b = b.substr(1, b.length());
  if (a[0] != '-')
    a = "+" + a;
  if (b[0] != '-')
    b = "+" + b;

  if (a[0] == '-') {
    if (b[0] != '-') {
      return "-" + add_whole(a.substr(1, a.length()), b.substr(1, b.length()));
    }
    if (b[0] == '-') {
      std::string a_copy = a;
      a = b.substr(1, b.length());
      b = a_copy.substr(1, a.length());
    }
  }
  if (b[0] == '-' && a[0] != '-') {
    return add_whole(a.substr(1, a.length()), b.substr(1, b.length()));
  }
  if (a[0] == '+' && b[0] == '+') {
    a = a.substr(1, a.length());
    b = b.substr(1, b.length());
  }

  char *ca = (char *)malloc(a.length() + 1);
  strcpy(ca, a.c_str());
  char *cb = (char *)malloc(b.length() + 1);
  strcpy(cb, b.c_str());
  char *res = (char *)malloc(std::max(a.length(), b.length()) + 5);
  if (a.length() == b.length())
    _subtract_whole_same_length(ca, cb, res);
  else
    _subtract_whole(ca, cb, res);
  std::string answer(res);
  free(ca);
  free(cb);
  free(res);
  remove_leading_zeroes_inplace(answer);
  return answer;
}
#endif

std::string subtract(std::string a, std::string b) {
  if (!(str_contains(a, '.') || str_contains(b, '.'))) {
    return subtract_whole(a, b);
  } else {
    if (!decimal_point_exists(a))
      a += ".0";
    if (!decimal_point_exists(b))
      b += ".0";
    if (a[0] == '.')
      a = "0" + a;
    if (b[0] == '.')
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
    return shift_decimal_point(subtract_whole(a, b), -1 * n_to_shift);
  }
}

#endif