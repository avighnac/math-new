#include <iostream>

#include "algorithms/Addition Algorithm/add.hpp"
#include "algorithms/Division Algorithm/divide.hpp"
#include "algorithms/Multiplication Algorithm/multiply.hpp"
#include "algorithms/Subtraction Algorithm/subtract.hpp"

#define RED "\033[31m"   /* Red */
#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
#define BOLD_WHITE "\033[1;37m"

#define TODO (std::cout << "You've discovered a feature that's not yet coded in! This will not be the case in some time. \n")

namespace basic_math_operations {
std::string add(const std::string &num1, const std::string &num2) {
  return ::add(num1, num2);
}
std::string subtract(const std::string &num1, const std::string &num2) {
  return ::subtract(num1, num2);
}
std::string multply(const std::string &num1, const std::string &num2) {
  return ::multiply(num1, num2);
}
std::string divide(const std::string &num1, const std::string &num2) {
  return ::divide(num1,
                  num2); /*Still in beta.
                            Only supports whole quotient division for now.*/
}
} // namespace basic_math_operations

std::string to_lower(std::string str) {
  for (auto &i : str)
    i = tolower(i);
  return str;
}

int main(int argCount, char *argument[]) {
  if (argCount == 1) {
    std::cout
        << "Syntax: math++ [function]. For more information run math++ help.\n";
  }

  if (argCount >= 2) {
    std::string function = argument[1];
    function = to_lower(function);

    if (function == "add") {
      if (argCount == 2) {
        std::cout << "\n(Developed by avighnac.) \nHint: Use math++ add [num1] "
                     "[num2] to skip this interface.\n\n";
        std::cout << "Amount of numbers to be added: ";

        size_t arr_size;
        std::cin >> arr_size;
        while (arr_size < 2) {
          std::cout << RED << "ERROR: Number too small. " << RESET
                    << "\nAmount of numbers to be added: ";
          std::cin >> arr_size;
        }

        std::string to_add[arr_size];
        std::cout << GREEN << "Numbers: (Separated with a space): " << RESET;
        for (int i = 0; i < arr_size; i++) {
          std::cin >> to_add[i];
        }
        std::string addition = "0";
        for (int i = 0; i < arr_size / 2; i++) {
          addition = basic_math_operations::add(
              addition, basic_math_operations::add(to_add[i], to_add[i + 1]));
        }
        if (arr_size % 2 != 0)
          addition = basic_math_operations::add(addition, to_add[arr_size - 1]);

        std::cout << GREEN << addition << "\n" << RESET;
      }

      else if (argCount == 3)
        std::cout << "Error: Insufficient Arguments! \n";

      else if (argCount == 4)
        std::cout << basic_math_operations::add(argument[2], argument[3])
                  << "\n";
    }

    if (function == "help") {
      std::cout
          << "\nMath++ is a free and open-source tool created by "
             "avighnac to solve math! For a full list of credits run math++ credits.\nFUNCTIONS:\n    •Add- Uses an addition algorithm implemented to add numbers.. infinitely huge.\n\nNote: For help "
             "with any individual function run math++ [function] help.\n\n";
    }

    if (function == "credits") {
      TODO;
    }

    if (function == "sqrt") {
      TODO;
    }

    if (function == "subtract") {
      TODO;
    }

    if (function == "divide") {
      TODO;
    }

    if (function == "multiply") {
      TODO;
    }
  }
}