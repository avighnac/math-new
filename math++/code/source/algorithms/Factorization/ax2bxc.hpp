#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <vector>

#include "../gcd.hpp"
#include "../get_terms.hpp"
#include "split_middle_term.hpp"

long long term_to_number(std::string term) {
  std::map<char, long long> numbers;
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
  return std::stoll(termStr);
}

struct bracket_term {
  long long term1, term2;
};

std::string ax2bxc(std::string sum) {
  sum.erase(std::remove(sum.begin(), sum.end(), ' '),
            sum.end()); // Remove spaces
  auto terms = get_terms(sum);

  std::map<char, long long> numbers;
  for (auto i = '0'; i <= '9'; i++)
    numbers.insert({i, i - 48});
  long long a, c;

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
  a = term_to_number(terms[0]), c = term_to_number(terms[2]);

  auto algebraicTerms = algebric_num::get_terms(sum);
  algebraicTerms[1].constantPart = "1";
  std::string variable = algebric_num::convert_to_readable({algebraicTerms[1]});
  variable.erase(std::remove(variable.begin(), variable.end(), ' '), variable.end());

  std::pair<long long, long long> secondTermSplit;
  auto temp = split_middle_term_ax2bxc(algebric_num::get_terms(sum));
  secondTermSplit.first = std::stoi(temp.first);
  secondTermSplit.second = std::stoi(temp.second);

  if (secondTermSplit.first * secondTermSplit.second != a * c)
    return "Cannot factorize further.";

  std::pair<bracket_term, bracket_term> answer;
  answer.first.term1 = gcd(a, secondTermSplit.first);
  answer.first.term2 = gcd(secondTermSplit.second, c);
  answer.second.term1 = a / answer.first.term1;
  answer.second.term2 = secondTermSplit.first / answer.first.term1;

  std::string preNumber = "1";
  auto gcd1 = gcd(answer.first.term1, answer.first.term2),
       gcd2 = gcd(answer.second.term1, answer.second.term2);
  preNumber = multiply(preNumber, std::to_string(gcd1));
  answer.first.term1 /= gcd1;
  answer.first.term2 /= gcd1;
  preNumber = multiply(preNumber, std::to_string(gcd2));
  answer.first.term1 /= gcd2;
  answer.first.term2 /= gcd2;

  if (preNumber[0] == '-') {
    if (answer.first.term1 < 0) {
      answer.first.term1 *= -1;
      answer.first.term2 *= -1;
    } else {
      answer.second.term1 *= -1;
      answer.second.term2 *= -1;
    }
    preNumber = preNumber.substr(1, preNumber.length() - 1);
  }

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
  return (preNumber == "1" ? "" : preNumber) + strAnswer;
}