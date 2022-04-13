#pragma once

#include <string>
#include <vector>

namespace arr_to_string {
std::string color(std::string text, std::string color) {
#define Black "\u001b[30m"
#define Red "\u001b[31m"
#define Green "\u001b[32m"
#define Yellow "\u001b[33m"
#define Blue "\u001b[34m"
#define Magenta "\u001b[35m"
#define Cyan "\u001b[36m"
#define White "\u001b[37m"
#define Reset "\u001b[0m"
  // #if defined(_WIN32)
  //   return text;
  // #endif

  if (color == "Black")
    return Black + text + Reset;
  else if (color == "Red")
    return Red + text + Reset;
  else if (color == "Green")
    return Green + text + Reset;
  else if (color == "Yellow")
    return Yellow + text + Reset;
  else if (color == "Blue")
    return Blue + text + Reset;
  else if (color == "Magenta")
    return Magenta + text + Reset;
  else if (color == "Cyan")
    return Cyan + text + Reset;
  else if (color == "White")
    return White + text + Reset;

  return "no not a color";
}

template <typename T>
std::string
array_to_string(std::vector<T> arr, std::string split = ", ",
                std::pair<std::string, std::string> brackets = {"[", "]"}) {
  if (arr.empty())
    return brackets.first + brackets.second;
  std::string result = brackets.first;
  for (auto i = 0; i < arr.size(); i++)
    result += std::to_string(arr[i]) + split;
  return result.substr(0, result.size() - split.length()) + brackets.second;
}

std::string
array_to_string(std::vector<std::string> arr, std::string split = ", ",
                std::pair<std::string, std::string> brackets = {"[", "]"}) {
  if (arr.empty())
    return brackets.first + brackets.second;
  std::string result = brackets.first;
  for (auto i = 0; i < arr.size(); i++)
    result += "\"" + arr[i] + "\"" + split;
  return result.substr(0, result.size() - split.length()) + brackets.second;
}

std::string array_to_string(std::vector<char> arr, std::string split = ", ",
                            std::pair<std::string, std::string> brackets = {
                                "[", "]"}) {
  if (arr.empty())
    return brackets.first + brackets.second;
  std::string result = brackets.first;
  for (auto i = 0; i < arr.size(); i++)
    result += "'" + std::string(1, arr[i]) + "'" + split;
  return result.substr(0, result.size() - split.length()) + brackets.second;
}

template <typename T>
std::string
subarray_to_string(std::vector<T> arr, size_t start, size_t elements,
                   std::string split = ", ",
                   std::pair<std::string, std::string> brackets = {"[", "]"}) {
  if (arr.empty())
    return brackets.first + brackets.second;
  std::string result = brackets.first;
  for (auto i = 0; i < arr.size(); i++)
    result += ((start <= i && i <= start + elements - 1)
                   ? color(std::to_string(arr[i]), "Green")
                   : color(std::to_string(arr[i]), "Red")) +
              split;
  return result.substr(0, result.size() - split.length()) + brackets.second;
}
} // namespace arr_to_string