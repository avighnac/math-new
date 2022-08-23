#pragma once
#include <string>

std::string inc(std::string x) {
  if (x.empty())
    return "1";
  x[x.size() - 1]++;
  bool shouldAdd = false;
  for (auto i = x.length(); i-- > 0;) {
    if (x[i] - 48 > 9) {
      (i == 0) ? shouldAdd = true : x[i - 1]++;
      x[i] -= 10;
    }
  }
  if (shouldAdd)
    x = "1" + x;
  return x;
}