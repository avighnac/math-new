#pragma once

#include <string>
#include <vector>

#include "../../../../basic_math_operations/basic_math_operations.hpp"

static void remove_trailing_zeroes(std::string &str) {
  str.erase(0, std::min(str.find_first_not_of('0'), str.size() - 1));
}

namespace separate_into_parts_help {
std::string reverse_string(std::string str) {
  std::reverse(str.begin(), str.end());
  return str;
}

std::vector<std::string> reverse_vec_str(const std::vector<std::string> &vec) {
  std::vector<std::string> answer;
  for (auto i = vec.size(); i-- > 0;) {
    answer.push_back(reverse_string(vec[i]));
  }
  return answer;
}

std::string combine_chars(char a, char b) {
  std::string answer;
  if (a != ' ')
    answer.push_back(a);
  if (b != ' ')
    answer.push_back(b);
  return answer;
}
} // namespace separate_into_parts_help

std::vector<std::string> separate_into_parts(std::string &str) {
  std::vector<std::string> answer;
  std::reverse(str.begin(), str.end());
  for (int i = 0; i < (int)str.length(); i += 2) {
    char a = ' ';
    char b = ' ';
    if (i < (int)str.length())
      a = str[i];
    if (i + 1 < (int)str.length())
      b = str[i + 1];

    answer.push_back(separate_into_parts_help::combine_chars(a, b));
  }

  return separate_into_parts_help::reverse_vec_str(answer);
}

namespace left_side_help {

std::vector<int> turn_to_digits(const std::string &str_n) {
  std::vector<int> answer;
  for (auto i : str_n)
    answer.push_back(i - 48);
  return answer;
}

bool smaller_than(const std::string &a1,
                  const std::string &b1) { // if a <= b return true;
  std::string a = a1;
  std::string b = b1;

  std::reverse(a.begin(), a.end());
  std::reverse(b.begin(), b.end());

  std::vector<int> a_vec = turn_to_digits(a);
  std::vector<int> b_vec = turn_to_digits(b);
  if (a.length() > b.length())
    for (auto i = 0; i < a.length() - b.length(); i++)
      b_vec.push_back(0);
  if (a.length() < b.length())
    for (auto i = 0; i < b.length() - a.length(); i++)
      a_vec.push_back(0);
  a_vec = reverse_vec(a_vec);
  b_vec = reverse_vec(b_vec);

  for (int i = 0; i < a_vec.size(); i++) {
    if (a_vec[i] > b_vec[i])
      return false;
    if (a_vec[i] < b_vec[i])
      return true;
  }

  return true;
}

bool greater_than(const std::string &a1, const std::string &b1) {
  return !smaller_than(a1, b1);
}

int box_filler(std::string &a, std::string &b,
               std::string &preLSColumnMultiplicationOut) {
  remove_trailing_zeroes(a);
  remove_trailing_zeroes(b);

  int start = 0, end = 9, answer = 0;

  while (start <= end) {
    int mid = (start + end) / 2;
    std::string preLSColumnMultiplication =
        multiply((a + std::to_string(mid)), std::to_string(mid));
    if (greater_than(preLSColumnMultiplication, b))
      end = mid - 1;
    else {
      preLSColumnMultiplicationOut = preLSColumnMultiplication;
      start = mid + 1;
      answer = mid;
    }
  }
  return answer;
}
} // namespace left_side_help

std::string integer_square_root(std::string n, int accuracy,
                                bool &negative_square_root) {
  if (n[0] == '-') {
    negative_square_root = true;
    n = n.substr(1, n.length() - 1);
  }

  std::string answer;
  std::string ls_column = "0";
  for (int i = 0; i < accuracy; i++) {
    n += "00";
  }

  std::vector<std::string> parts = separate_into_parts(n); // Split Into Parts

  for (int i = 0; i < parts.size(); i++) {

    const std::string &part = parts[i]; // Find quotient
    std::string preLSColumnMultiplication;
    int quotient = left_side_help::box_filler(ls_column, parts[i],
                                              preLSColumnMultiplication);
    answer += std::to_string(quotient);

    ls_column += std::to_string(quotient); // ls_column = ls_column + quotient

    std::string remainder = subtract(
        part, preLSColumnMultiplication); // CP - quotient * ls_column = rem

    if ((i + 1) < parts.size())
      parts[i + 1] = remainder + parts[i + 1]; // part = rem + part

    ls_column = add(ls_column, std::to_string(quotient));
  }

  answer = answer.substr(0, answer.length() - accuracy) + "." +
           answer.substr(answer.length() - accuracy, answer.length());
  if (answer[answer.length() - 1] == '.')
    answer = answer.substr(0, answer.length() - 2);
  size_t decimal_point_location = answer.length() - accuracy - 1;
  bool is_all_zeroes = true;
  for (auto &i : answer.substr(decimal_point_location + 1, answer.length()))
    if (i != '0')
      is_all_zeroes = false;
  if (is_all_zeroes)
    answer = answer.substr(0, decimal_point_location);

  return answer;
}

std::string integer_square_root(std::string n, int accuracy) {
  bool i;
  return integer_square_root(n, accuracy, i);
}

std::string square_root(std::string number, int accuracy) {
  if (decimal_point_exists(number)) {
    size_t DPL = decimal_point_location(number);
    size_t x = number.substr(DPL + 1, number.length()).length();
    if (x & 1) {
      x++;
      number += "0";
    }

    std::string number_temp;
    for (auto &i : number)
      if (i != '.')
        number_temp.push_back(i);
    number = number_temp;

    bool i = false;
    std::string sqrt = integer_square_root(number, accuracy - (x / 2), i);
    if (!decimal_point_exists(sqrt))
      sqrt += ".0";
    size_t dec_loc = decimal_point_location(sqrt);
    while (sqrt.substr(0, dec_loc).length() < (x / 2) + 1) {
      sqrt = "0" + sqrt;
      dec_loc++;
    }
    std::string sqrt_temp;
    for (auto &i : sqrt)
      if (i != '.')
        sqrt_temp.push_back(i);
    sqrt = sqrt_temp;
    sqrt = sqrt.substr(0, dec_loc - (x / 2)) + "." +
           sqrt.substr(dec_loc - (x / 2), sqrt.length());

    std::reverse(sqrt.begin(), sqrt.end());
    sqrt.erase(0, std::min(sqrt.find_first_not_of('0'), sqrt.size() - 1));
    std::reverse(sqrt.begin(), sqrt.end());
    return sqrt + (i ? "i" : "");
  } else {
    bool i = false;
    std::string square_root = integer_square_root(number, accuracy, i);
    square_root.erase(0, std::min(square_root.find_first_not_of('0'),
                                  square_root.size() - 1));
    return square_root + (i ? "i" : "");
  }
}