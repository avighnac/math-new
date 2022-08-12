#pragma once

std::vector<std::string> get_terms(std::string s) {
  if (!(s.length() == 0)) {
    if (s[0] != '+' && s[0] != '-')
      s = "+" + s;
  } else
    return {};
  std::vector<std::string> answer;
  std::string currentTerm;
  for (auto i = 1; i < s.length(); i++) {
    if (s[i] == '+' || s[i] == '-' && s[i - 1] != '^') {
      answer.push_back(currentTerm);
      currentTerm.clear();
      currentTerm.push_back(s[i]);
    } else
      currentTerm.push_back(s[i]);
  }
  answer.push_back(currentTerm);
  if (!answer.empty())
    answer[0] = s.substr(0, 1) + answer[0];

  return answer;
}