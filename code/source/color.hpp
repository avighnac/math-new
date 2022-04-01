#pragma once

#include <string>

#define Black "\u001b[30m"
#define Red "\u001b[31m"
#define Green "\u001b[32m"
#define Yellow "\u001b[33m"
#define Blue "\u001b[34m"
#define Magenta "\u001b[35m"
#define Cyan "\u001b[36m"
#define White "\u001b[37m"
#define Reset "\u001b[0m"

std::string color(std::string text, std::string color) {
#if defined(_WIN32)
  return text;
#endif

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