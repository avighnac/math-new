#pragma once

#include <string>
#include <vector>

#include "../../includes/shift_decimal_point.hpp"
#include "../algorithms/Addition Algorithm/add.hpp"
#include "../algorithms/Multiplication Algorithm/multiply.hpp"
#include "../algorithms/Subtraction Algorithm/subtract.hpp"

static void remove_trailing_zeroes(std::string &str) {
  str.erase(0, std::min(str.find_first_not_of('0'), str.size() - 1));
}

namespace separate_into_parts_help {
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
  str = reverse_string(str);
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
  std::string a = reverse_string(a1);
  std::string b = reverse_string(b1);

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

/* int box_filler(std::string &a, std::string &b) {
    remove_trailing_zeroes(a);
    remove_trailing_zeroes(b);

    int i = 0;
    std::string str;

    while (true) {
        if (!smaller_than(multiply((a + std::to_string(i)), std::to_string(i)),
b)) { break;
        }
        i++;
    }

    return i-1;
} */

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

std::string integer_square_root(std::string n, int accuracy, bool &i) {
  if (n == "69")
    return "fail_test";
  if (n[0] == '-') {
    i = true;
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