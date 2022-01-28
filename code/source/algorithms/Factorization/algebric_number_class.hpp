#include <map>
#include <string>
#include <vector>

namespace algebric_num {
struct variable {
  std::string var;
  int power = 1;
};

class algebric_number {
private:
  size_t find_first_of(size_t, size_t, std::string, std::string);

  // Note that the number will be constantPart * variablePart
  // and not '+' as any + or - signs will split the term into
  // two.

public:
  std::string constantPart;
  std::map<char, int> variablePart;

  algebric_number(std::string);
  void print_number();
  std::string get_formatted_number();
  std::string char_to_str(char);
  ~algebric_number();
};

algebric_number::algebric_number(std::string term) {
  // 10^2a^2b^2
  // constant: 10^2
  // variable: {{a, power: 2}, {b, power: 2}}

  std::string constantString = "1";
  bool isConstantStringModified = false;

  for (auto &i : term) {
    if (!('a' <= i && i <= 'z')) {
      if (!isConstantStringModified) {
        isConstantStringModified = true;
        constantString.clear();
      }
      constantString.push_back(i);
    } else { // If current character is a letter
      // This also means all of the constant part has now been taken care of.
      break;
    }
  }

  if (constantString !=
      "1") // This gets rid of the constant part from the string.
    term = term.substr(constantString.length(), term.length());

  if (constantString.find('^') == std::string::npos) {
    constantPart = constantString; // Assign value to variable.
    constantString.clear();
  } else {
    std::string constantNonPowerPart;
    int count = 0;
    for (auto &i : constantString) {
      if (i == '^')
        break;
      constantNonPowerPart.push_back(i);
      count++;
    }
    std::string constantPowerPart =
        constantString.substr(count + 1, constantString.length() - count + 1);
    std::string finalAnswer = "1";
    for (auto i = 0; i < abs(std::stoll(constantPowerPart)); i++)
      finalAnswer = multiply(finalAnswer, constantNonPowerPart);
    if (std::stoll(constantPowerPart) >= 0)
      constantPart = finalAnswer;
    else
      // constantPart = divide(1, finalAnswer);
      // This line does not work as the divide() function does not support
      // decimals yet.

      constantPart = std::to_string(1.0 / std::stoll(finalAnswer));
  }

  if (constantPart == "+0" || constantPart == "-0" || constantPart == "0")
    variablePart = {};
  else {
    char currentVar;

    for (auto i = 0; i < (int)(term.length()); i++) {
      auto &cv = term[i];
      bool justInserted = false;
      if ('a' <= cv && cv <= 'z') {
        if (variablePart.find(cv) == variablePart.end()) {
          if (term[i + 1] == '^') {
            variablePart.insert({cv, 0});
          } else {
            justInserted = true;
            variablePart.insert({cv, 1});
          }
          currentVar = cv;
        }
        if (term[i + 1] != '^' && !justInserted) {
          variablePart.find(cv)->second++;
          justInserted = false;
        }
        if (i + 2 <= term.length() - 1) {
          if (term[i + 1] == '^') {
            variablePart.find(cv)->second += std::stoi(
                term.substr(i + 2, find_first_of(i + 2, term.length() - 1,
                                                 "letter", term)));
          }
        }
      }
    }
  }
}

algebric_number::~algebric_number() {}

void algebric_number::print_number() {
  std::cout << "Constant Part: " << constantPart << "\nVariables: {";

  std::string toPrint;
  for (auto &i : variablePart) {
    toPrint += "{" + char_to_str(i.first) +
               ", power: " + std::to_string(i.second) + "}, ";
  }
  toPrint = toPrint.substr(0, toPrint.length() - 2);

  std::cout << toPrint << "}\n";
}

std::string algebric_number::get_formatted_number() {
  std::string answer;
  answer += "{" + constantPart + ", {";
  for (auto &i : variablePart) {
    answer += "{" + char_to_str(i.first) +
               ", power: " + std::to_string(i.second) + "}, ";
  }
  if (!variablePart.empty())
    answer = answer.substr(0, answer.length() - 2);

  return answer + "}}";
}

size_t algebric_number::find_first_of(size_t startPos, size_t endPos,
                                      std::string argument, std::string term) {

  if (argument == "letter") {
    for (auto i = startPos; i <= endPos; i++) {
      if ('a' <= term[i] && term[i] <= 'z')
        return i;
    }

    return -1;
  }

  return -1;
}

std::string algebric_number::char_to_str(char charac) {
  std::string answer;
  answer.push_back(charac);
  return answer;
}

void erase_algebric_number(std::vector<algebric_num::algebric_number> &algebricTerms,
                           size_t index) {
  std::vector<algebric_num::algebric_number> answer;
  for (auto i = 0; i < algebricTerms.size(); i++)
    if (i != index)
      answer.push_back(algebricTerms[i]);
  algebricTerms = answer;
}

std::string
convert_to_readable(std::vector<algebric_num::algebric_number> &algebricTerms) {
  std::string answer;
  int counter = 0;
  for (auto &i : algebricTerms) {
    if (i.constantPart[0] != '-')
      answer += "+ ";
    else
      (counter == 0) ? answer += "-" : answer += "- ";
    if ((i.constantPart != "1" && i.constantPart != "-1") || i.variablePart.empty()) {
      if (i.constantPart[0] == '-')
        answer += i.constantPart.substr(1, i.constantPart.length() - 1);
      else
        answer += i.constantPart;
    }

    for (auto &j : i.variablePart) {
      answer.push_back(j.first);
      if (j.second != 1)
        answer += "^" + std::to_string(j.second);
    }
    answer += " ";
    counter++;
  }
  if (!answer.empty())
    if (answer[0] == '+')
      return answer.substr(2, answer.length() - 2);
  return answer;
}
} // namespace algebric_num