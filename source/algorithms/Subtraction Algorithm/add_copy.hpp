#include <string>
#include <algorithm>
#include <vector>
#include "../../../includes/shift_decimal_point.hpp"

#ifndef _add_copy_hpp_
#define _add_copy_hpp_
static bool str_contains_copy (const std::string &str, char charac) {  for (auto &i : str) if (i == charac) return true;  return false;}

std::vector<int> digitize_copy(std::string str_n)  {
  std::vector<int> answer;
  for (int i = str_n.length()-1; i > -1; i--) {
    answer.push_back(str_n[i]-48);
  }
  return answer;
}

static std::string add_whole_copy(const std::string& a1, const std::string& b1) {
  std::string a = a1;
  std::string b = b1;
  if (a1 == "") a = "0";
  if (b1 == "") b = "0";

  std::vector<int> a_vec = digitize_copy(a);
  std::vector<int> b_vec = digitize_copy(b); 
  if (a.length() > b.length()) for (auto i=0; i<a.length()-b.length(); i++) b_vec.push_back(0);
  if (a.length() < b.length()) for (auto i=0; i<b.length()-a.length(); i++) a_vec.push_back(0);

  std::vector<int> addition;
  for (int i=0; i<(int)a_vec.size(); i++) addition.push_back(a_vec[i] + b_vec[i]); //Adding every digit of a and b

  for (int i=0; i<(int)a_vec.size(); i++) {
      if (std::to_string(addition[i]).length() == 2 && i != a_vec.size()-1) {
          int carry_forward = addition[i] / 10;
          addition[i+1] += carry_forward;
          addition[i] -= carry_forward * 10;
      }
  }

  std::string answer;
  for (int i = addition.size()-1; i > -1; i--) answer += std::to_string(addition[i]); //Re-Reversing the array

  return answer;
}

std::string add_copy(std::string a, std::string b) {
  if (!(str_contains_copy(a, '.') || str_contains_copy(b, '.'))) {
    return add_whole_copy(a, b);
  }
  else {
    if (!decimal_point_exists(a)) a += ".0";
    if (!decimal_point_exists(b)) b += ".0";
    if (a[1] == '.') a = "0" + a;
    if (b[1] == '.') b = "0" + b;
    size_t a_dec_loc = decimal_point_location(a);
    size_t b_dec_loc = decimal_point_location(b); 

    //We want to make sure digits before and after decimal are equal
    size_t a_digits_after_decimal = a.substr(a_dec_loc + 1, a.length()).length();
    size_t b_digits_after_decimal = b.substr(b_dec_loc + 1, b.length()).length();
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

    if (a.length() > b.length()) for (auto i=0; i<a.length()-b.length(); i++) {b = "0" + b; b_dec_loc++;}
    if (a.length() < b.length()) for (auto i=0; i<b.length()-a.length(); i++) {a = "0" + a; a_dec_loc++;}

    const size_t n_to_shift = a.substr(a_dec_loc + 1, a.length()).length();
    a.erase(a_dec_loc, 1);
    b.erase(b_dec_loc, 1);
    return shift_decimal_point(add_whole_copy(a, b), -n_to_shift);
  }
}
#endif
