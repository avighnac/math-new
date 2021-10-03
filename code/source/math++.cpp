#include <chrono>
#include <iostream>

#include "algorithms/Addition Algorithm/add.hpp"
#include "algorithms/Division Algorithm/divide.hpp"
#include "algorithms/Multiplication Algorithm/multiply.hpp"
#include "algorithms/Subtraction Algorithm/subtract.hpp"
#include "algorithms/integer_square_root.hpp"

#define RED "\033[31m"   /* Red */
#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
#define BOLD_WHITE "\033[1;37m"

#define TODO                                                                   \
  (std::cout << "You've discovered a feature that's not yet coded in! This "   \
                "will not be the case in some time. \n")

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
        std::cout << "\nTip: Use math++ add [num1] "
                     "[num2] to skip this interface.\n\n";
        std::cout << "Amount of numbers to be added: ";

        size_t arr_size;
        std::cin >> arr_size;
        while (arr_size < 2) {
          std::cout << RED << "Error: Number too small. " << RESET
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

      else if (argCount == 3) {
        std::string thirdArg = argument[2];
        if (thirdArg == "help")
          TODO;
        else
          std::cout
              << "[math++.function.add] Error: Insufficient Arguments! \n";
      }

      else if (argCount == 4)
        std::cout << basic_math_operations::add(argument[2], argument[3])
                  << "\n";
    }

    if (function == "help") {
      std::cout
          << "\nMath++ is a free and open-source tool created by "
             "avighnac to solve math! For a full list of credits run math++ "
             "credits.\nFUNCTIONS:\n    •Add- Uses an addition algorithm "
             "implemented to add numbers.. infinitely huge.\n    •Subtract- "
             "Same as addition, but for subtraction!\n    •Square Root- The "
             "square root of a number is a number which when multiplied, gives "
             "you the original number back.\n\nNote: For help "
             "with any individual function run math++ [function] help.\n\n";
    }

    if (function == "credits") {
      TODO;
    }

    if (function == "sqrt") {
      if (argCount >= 3) {
        std::string argument3 = argument[2];
        if (argument3 != "help") {
          int accuracy = 8;
          bool show_time = false;
          if (argCount >= 4) {
            accuracy = std::stoi(argument[3]);
          }
          if (argCount >= 5) {
            std::string arg5 = argument[4];
            if (arg5 == "-t") {
              show_time = true;
            }
          }

          if (decimal_point_exists(argument[2])) {
            std::chrono::time_point<std::chrono::high_resolution_clock> start;
            std::chrono::time_point<std::chrono::high_resolution_clock> stop;
            if (show_time)
              start = std::chrono::high_resolution_clock::now();
            std::string number = argument[2];
            size_t DPL = decimal_point_location(number);
            size_t x = number.substr(DPL + 1, number.length()).length();
            if (x % 2 != 0) {
              x++;
              number += "0";
            }

            std::string number_temp;
            for (auto &i : number)
              if (i != '.')
                number_temp.push_back(i);
            number = number_temp;

            std::string sqrt = integer_square_root(number, accuracy - (x / 2));
            if (!decimal_point_exists(sqrt))
              sqrt += ".0";
            size_t dec_loc = decimal_point_location(sqrt);
            while (sqrt.substr(0, dec_loc).length() < (x / 2) + 1) {
              sqrt = "0" + sqrt;
              dec_loc++;
            }
            std::string sqrt_temp;
            for (auto &i : sqrt)
              if (i != '.')
                sqrt_temp.push_back(i);
            sqrt = sqrt_temp;
            sqrt = sqrt.substr(0, dec_loc - (x / 2)) + "." +
                   sqrt.substr(dec_loc - (x / 2), sqrt.length());

            std::reverse(sqrt.begin(), sqrt.end());
            sqrt.erase(0,
                       std::min(sqrt.find_first_not_of('0'), sqrt.size() - 1));
            std::reverse(sqrt.begin(), sqrt.end());
            if (show_time)
              stop = std::chrono::high_resolution_clock::now();
            std::cout << GREEN << "±" << RESET << sqrt << "\n";
            if (show_time) {
              auto time = std::chrono::duration_cast<std::chrono::microseconds>(
                              stop - start)
                              .count() /
                          100000.0;
              std::cout << "\nTime taken: " << time << " seconds. \n";
            }
          } else {
            std::chrono::time_point<std::chrono::high_resolution_clock> start;
            std::chrono::time_point<std::chrono::high_resolution_clock> stop;
            if (show_time)
              start = std::chrono::high_resolution_clock::now();
            std::string square_root =
                integer_square_root(argument[2], accuracy);
            square_root.erase(0, std::min(square_root.find_first_not_of('0'),
                                          square_root.size() - 1));
            if (show_time)
              stop = std::chrono::high_resolution_clock::now();
            std::cout << GREEN << "±" << RESET << square_root << "\n";

            if (show_time) {
              auto time = std::chrono::duration_cast<std::chrono::microseconds>(
                              stop - start)
                              .count() /
                          1000000.0;
              std::cout << "\nTime taken: " << time << " seconds. \n";
            }
          }
        } else {
          std::cout << "Syntax: math++ sqrt [number] [accuracy] [-t for "
                       "displaying time "
                       "taken] \n";
        }
      }
    }

    if (function == "subtract") {
      if (argCount == 2) {
        std::string num1, num2;

        std::cout << "\nTip: Use math++ subtract [num1] "
                     "[num2] to skip this interface.\n\n";
        std::cout << GREEN << "Number 1: " << RESET;
        std::cin >> num1;
        std::cout << GREEN << "Number 2: " << RESET;
        std::cin >> num2;

        std::cout << GREEN << subtract(num1, num2) << "\n" << RESET;
      }

      else if (argCount == 3) {
        std::string thirdArg = argument[2];
        if (thirdArg == "help")
          TODO;
        else
          std::cout
              << "[math++.function.subtract] Error: Insufficient Arguments! \n";
      } else if (argCount == 4)
        std::cout << basic_math_operations::subtract(argument[2], argument[3])
                  << "\n";
    }

    if (function == "divide") {
      TODO;
    }

    if (function == "multiply") {
      TODO;
    }
  }
}