#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <vector>

#include "../gcd.hpp"
#include "../get_terms.hpp"
#include "split_middle_term.hpp"

int term_to_number(std::string term) {
  std::map<char, int> numbers;
  for (auto i = '0'; i <= '9'; i++)
    numbers.insert({i, i - 48});

  std::string termStr;
  for (auto i = 1; i < term.length(); i++)
    if (numbers.find(term[i]) !=
        numbers.end()) // If the i'th character is a number
      termStr.push_back(term[i]);
    else
      break;
  termStr = term[0] + termStr;
  return std::stoi(termStr);
}

struct bracket_term {
  int term1, term2;
};

// TODO: FIX BUG which accepts "ab^2 + 3ab + 2"
// but doesn't accept "a^2b^2 + 3ab + 2" which is correct.
// The first one is WRONG.

std::string ax2bxc(std::string sum) {
  sum.erase(std::remove(sum.begin(), sum.end(), ' '),
            sum.end()); // Remove spaces
  auto terms = get_terms(sum);

  std::map<char, int> numbers;
  for (auto i = '0'; i <= '9'; i++)
    numbers.insert({i, i - 48});
  int a, b, c;

  if (numbers.find(terms[0][1]) ==
      numbers.end()) // If the second character ([0] will be the sign) of
                     // the first term is not a number
    terms[0] =
        terms[0].substr(0, 1) + "1" +
        terms[0].substr(1, terms[0].length() -
                               1); // This converts something like -x^2 to -1x^2
  if (numbers.find(terms[1][1]) == numbers.end()) // Same thing for second term
    terms[1] =
        terms[1].substr(0, 1) + "1" + terms[1].substr(1, terms[1].length() - 1);

  // Assigning terms to a, b, c
  a = term_to_number(terms[0]), b = term_to_number(terms[1]),
  c = term_to_number(terms[2]);
  std::string variable =
      terms[0].substr(std::to_string(a).length() + 1,
                      (terms[0].find('^') - std::to_string(a).length() - 1));

  std::pair<int, int> secondTermSplit;
  auto product = a * c;

  for (float i = 0; i < abs(product); i++) {
    float number = product / i;
    if (std::ceil(number) == number) {
      if (number + i == b) {
        secondTermSplit = {number, i};
        break;
      }
      if (-1 * number + i == b) {
        secondTermSplit = {-1 * number, i};
        break;
      }
      if (number + -1 * i == b) {
        secondTermSplit = {number, -1 * i};
        break;
      }
      if (-1 * number + -1 * i == b) {
        secondTermSplit = {-1 * number, -1 * i};
        break;
      }
    }
  }
  

  if (secondTermSplit.first == 0 && secondTermSplit.second == 0)
    return "Cannot factorize further.";

  std::pair<bracket_term, bracket_term> answer;
  answer.first.term1 = gcd(a, secondTermSplit.first);
  answer.first.term2 = gcd(secondTermSplit.second, c);
  answer.second.term1 = a / answer.first.term1;
  answer.second.term2 = secondTermSplit.first / answer.first.term1;

  std::string strAnswer = "(";
  if (answer.first.term1 == 1)
    strAnswer += variable;
  else
    strAnswer += std::to_string(answer.first.term1) + variable;
  if (answer.first.term2 > 0)
    strAnswer += " + " + std::to_string(answer.first.term2);
  else
    strAnswer += std::to_string(answer.first.term2);
  strAnswer += ")(";
  if (answer.second.term1 == 1)
    strAnswer += variable;
  else
    strAnswer += std::to_string(answer.second.term1) + variable;
  if (answer.second.term2 > 0)
    strAnswer += " + " + std::to_string(answer.second.term2);
  else
    strAnswer += std::to_string(answer.second.term2);
  strAnswer += ")";

  for (auto i = 0; i < strAnswer.length() - 1; i++) {
    if (strAnswer[i + 1] == '-') {
      strAnswer.insert(i + 1, " ");
      strAnswer.insert(i + 3, " ");
      i += 2;
    }
  }
  return strAnswer;
}