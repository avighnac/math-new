#pragma once

#include "../../../../basic_math_operations/basic_math_operations.hpp"
#include <algorithm>
#include <iostream>
#include <string>

static void replace_all(std::string &str, const std::string &from,
                        const std::string &to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

static size_t get_matching_brace(std::string str, size_t index) {
  if (str[index] != '(')
    return -1;
  int count = 0;
  for (size_t i = index; i < str.length(); i++) {
    if (str[i] == '(')
      count++;
    if (str[i] == ')')
      count--;

    if (!count)
      return i;
  }
  return -1;
}

std::string fetch(std::string s, bool left, long long &ind) {
  std::string a;
  bool encounteredNumbers = false;
  if (left) {
    bool encounteredMinus = false;
    ind--;
    while (ind >= 0) {
      if (s[ind] == '*' || s[ind] == '/' || s[ind] == '+')
        break;
      if (encounteredMinus)
        break;
      if (s[ind] == '-') {
        encounteredMinus = true;
      }
      a.push_back(s[ind]);
      ind--;
    }
    ind++;
    std::reverse(a.begin(), a.end());
  } else {
    ind++;
    while (ind < (long long)(s.length())) {
      if (!encounteredNumbers)
        encounteredNumbers = ('0' <= s[ind] && s[ind] <= '9');
      if (s[ind] == '*' || s[ind] == '/' || s[ind] == '+')
        break;
      if (s[ind] == '-')
        if (encounteredNumbers)
          break;
      a.push_back(s[ind]);
      ind++;
    }
    ind--;
  }
  return a;
}

void clean_double_signs(std::string &expression) {
  while ((expression.find("--") != std::string::npos) ||
         (expression.find("++") != std::string::npos) ||
         (expression.find("-+") != std::string::npos) ||
         (expression.find("+-") != std::string::npos)) {
    replace_all(expression, "--", "+");
    replace_all(expression, "-+", "-");
    replace_all(expression, "+-", "-");
    replace_all(expression, "++", "+");
  }
  replace_all(expression, "*+", "*");
  replace_all(expression, "/+", "/");
}

long long find_sign(std::string expression, char sign) {
  for (size_t find = 0; find < expression.length(); find++) {
    if (expression[find] == sign) {
      if (find == std::string::npos) {
        return -1;
      }
      bool numberEncountered = false;
      for (size_t i = 0; i < find; i++) {
        if ('0' <= expression[i] && expression[i] <= '9') {
          numberEncountered = true;
        }
      }
      if (numberEncountered) {
        return (long long)(find);
      }
    }
  }
  return -1;
}

void replace_from_pos(size_t start, size_t end, std::string &expression,
                      std::string answer) {
  std::string temp;
  bool done = false;
  for (size_t i = 0; i < expression.length(); i++) {
    if (start <= i && i <= end && !done) {
      done = true;
      temp += (answer[0] != '-' ? "+" : "") + answer;
      i = end;
    } else {
      temp.push_back(expression[i]);
    }
  }
  expression = temp;
}

template <typename T> T get_min(T a, T b) {
  if (a == -1)
    return b;
  if (b == -1)
    return a;
  return a > b ? b : a;
}

template <typename T> bool cmp(T a, T b) {
  if (a == -1)
    return false;
  if (b == -1)
    return true;

  return a < b;
}

std::string arithmeticEvaluate(std::string expression, int accuracy) {
  replace_all(expression, " ", "");
  clean_double_signs(expression);

  while (expression.find('(') != std::string::npos) {
    size_t start = expression.find('(');
    size_t end = get_matching_brace(expression, start);

    replace_all(expression, expression.substr(start, end - start + 1),
                arithmeticEvaluate(
                    expression.substr(start + 1, end - start - 1), accuracy));
  }

  clean_double_signs(expression);

  long long find = find_sign(expression, '/');
  while (find >= 0) {
    long long start = find, end = find;
    std::string s1 = fetch(expression, true, start),
                s2 = fetch(expression, false, end);
    std::string answer = divide(s1, s2, accuracy);

    replace_from_pos(start, end, expression, answer);
    find = find_sign(expression, '/');
  }

  clean_double_signs(expression);

  find = find_sign(expression, '*');
  while (find >= 0) {
    long long start = find, end = find;
    std::string answer =
        multiply(fetch(expression, true, start), fetch(expression, false, end));

    replace_from_pos(start, end, expression, answer);
    find = find_sign(expression, '*');
  }

  clean_double_signs(expression);

  find = find_sign(expression, '+');
  while (find >= 0) {
    long long start = find, end = find;
    std::string answer =
        add(fetch(expression, true, start), fetch(expression, false, end));

    replace_from_pos(start, end, expression, answer);
    find = find_sign(expression, '+');
  }

  clean_double_signs(expression);

  find = find_sign(expression, '-');
  while (find >= 0) {
    long long start = find, end = find;
    std::string answer =
        subtract(fetch(expression, true, start), fetch(expression, false, end));

    replace_from_pos(start, end, expression, answer);
    find = find_sign(expression, '-');
  }

  clean_double_signs(expression);
  if (expression[0] == '+')
    expression = expression.substr(1, expression.length());

  return expression;
}