#pragma once

#include "../Addition Algorithm/add.hpp"
#include "../shift_decimal_point.hpp"
#include <string>
#include <vector>

#ifndef _digitize_
#define _digitize_
static std::vector<int> digitize(std::string str_n) {
  std::vector<int> answer;
  for (int i = str_n.length() - 1; i > -1; i--)
    answer.push_back(str_n[i] - 48);
  return answer;
}
#endif

#ifndef _add_
#define _add_

static std::string add(const std::string &a1, const std::string &b1) {
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
  for (int i = 0; i < (int)a_vec.size(); i++)
    addition.push_back(a_vec[i] + b_vec[i]); // Adding every digit of a and b

  for (int i = 0; i < (int)a_vec.size(); i++) {
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

#endif

#ifndef _multiply_
#define _multiply_
static std::string multiply_whole(std::string a, std::string b) {
  std::vector<int> a_vec = digitize(a);
  std::vector<int> b_vec = digitize(b);

  std::vector<std::vector<int>> to_add;

  for (int i = 0; i < b_vec.size(); i++) {
    std::vector<int> to_push;
    for (int j = 0; j < i; j++)
      to_push.push_back(0);
    for (int j = 0; j < a_vec.size(); j++)
      to_push.push_back(b_vec[i] * a_vec[j]);
    to_add.push_back(to_push);
  }

  for (int i = 0; i < to_add.size();
       i++) { // Here, to_add[i] will be every element in to_add    //This
              // enitre thing is to deal with carry forwards
    for (int j = 0; j < to_add[i].size();
         j++) { // to_add[i][j] will be every element in to_add[i]
      if (std::to_string(to_add[i][j]).length() > 1 &&
          j != to_add[i].size() - 1) {
        int carry_forward = to_add[i][j] / 10;
        to_add[i][j + 1] += carry_forward;
        to_add[i][j] -= carry_forward * 10;
      }
    }
  }

  std::vector<std::string> str_to_add;
  for (auto i : to_add) {
    std::string str = "";
    for (int j = i.size() - 1; j > -1; j--)
      str += std::to_string(i[j]);
    str_to_add.push_back(str);
  }

  std::string answer = "0";
  for (auto i : str_to_add)
    answer = add(answer, i);

  return answer;
}

std::string multiply(std::string a, std::string b) {
  if (a.empty())
    a = "0";
  if (b.empty())
    b = "0";

  char sign = '+';
  if (a[0] == '-' && b[0] != '-') {
    sign = '-';
    a = a.substr(1, a.length());
  }
  if (b[0] == '-' && a[0] != '-') {
    sign = '-';
    b = b.substr(1, b.length());
  }
  if (a[0] == '-' && b[0] == '-') {
    a = a.substr(1, a.length());
    b = b.substr(1, b.length());
  }

  if (a[0] == '.')
    a = "0" + a;
  if (b[0] == '.')
    b = "0" + b;
  if (!decimal_point_exists(a))
    a += ".0";
  if (!decimal_point_exists(b))
    b += ".0";

  size_t a_dec_loc = decimal_point_location(a);
  size_t b_dec_loc = decimal_point_location(b);

  int n_to_shift = a.substr(a_dec_loc + 1, a.length()).length() +
                   b.substr(b_dec_loc + 1, b.length()).length();

  a.erase(a_dec_loc, 1);
  b.erase(b_dec_loc, 1);

  std::string answer = shift_decimal_point(multiply_whole(a, b), -n_to_shift);
  if (sign == '-')
    answer = "-" + answer;
  return answer;
}
#endif