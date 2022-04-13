#define NOMINMAX
#define CURL_STATICLIB

#include <chrono>
#include <curl/curl.h>

#include <fstream>
#include <iostream>

#include <basic_math_operations.hpp>

#include "code/source/algorithms/Simple Interest/simple_interest.hpp"
#include "code/source/algorithms/integer_square_root.hpp"
#include "code/source/algorithms/simplify_fractions.hpp"

#include "code/source/algorithms/Factorization/algebric_number_class.hpp"
#include "code/source/algorithms/Factorization/ax2bxc.hpp"

#include "code/source/color.hpp"

#include "code/source/algorithms/nroot.hpp"

#include <arr_to_string.hpp>

#include "code/source/algorithms/primeFactor.hpp"

// External Image Library
// #include "libraries/CImg.h"

#define RED "\033[31m"   /* Red */
#define GREEN "\033[32m" /* Green */
#define RESET "\033[0m"
#define BOLD_WHITE "\033[1;37m"

#define TODO                                                                   \
  (std::cout << "You've discovered a feature that's not yet coded in! This "   \
                "will not be the case in some time. \n")

bool is_windows() {
#if defined(_WIN32)
  return true;
#endif
  return false;
}

void replace_all(std::string &str, const std::string &from,
                 const std::string &to) {
  if (from.empty())
    return;
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

std::string latest_version;

inline size_t curl_get_latest_version(char *buffer, size_t itemsize,
                                      size_t nitems, void *ignorethis) {
  size_t bytes = itemsize * nitems;
  latest_version = std::string(buffer, bytes);
  return bytes;
}

template <typename T> std::string print_pair(std::pair<T, T> p) {
  return "{" + p.first + ", " + p.second + "}";
}

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
                     "[num2] ... [numN] to skip this interface.\n\n";
        std::cout << "Amount of numbers to be added: ";

        size_t arr_size;
        std::cin >> arr_size;
        while (arr_size < 2) {
          std::cout << RED << "Error: Number too small. " << RESET
                    << "\nAmount of numbers to be added: ";
          std::cin >> arr_size;
        }

        std::vector<std::string> to_add(arr_size);
        std::cout << GREEN << "Numbers: (Separated with a space): " << RESET;
        for (int i = 0; i < arr_size; i++) {
          std::cin >> to_add[i];
        }
        std::string addition = "0";
        for (int i = 0; i < arr_size / 2; i++) {
          addition = add(
              addition, add(to_add[i], to_add[i + 1]));
        }
        if (arr_size % 2 != 0)
          addition = add(addition, to_add[arr_size - 1]);

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

      else if (argCount >= 4) {
        std::string answer = "0";

        for (auto i = 2; i < argCount; i++)
          answer = add(answer, argument[i]);

        std::cout << answer << "\n";
      }
    }

    if (function == "help") {
      std::vector<std::string> functions = {
          "Add",
          "Subtract",
          "Multiply",
          "Divide",
          "Square Root",
          "Nth Root (nroot) (experimental)",
          "Fraction Simplifier",
          "Simple Interest",
          "Factorial",
          "Factorize",
          "Evaluate",
          "Decimal to Fraction",
      };
      std::vector<std::string> function_definitions = {
          "Uses an addition algorithm "
          "implemented to add numbers.. infinitely huge.",
          ""
          "Same as addition, but for subtraction!",
          "Multiply two or more numbers at once.",
          "Divide two numbers.",
          "The "
          "square root of a number is a number which when multiplied, gives "
          "you the original number back.",
          "Find the nth root of any number! (number)^(1/n)",
          "Simplifies a fraction to it's lowest terms.",
          "Solves simple interest sums automatically (with working). Google "
          "\"Simple Interest\" for more information.",
          "The number of ways to arrange n distinct objects into an ordered "
          "sequence of n places. For example, the number of ways to distribute "
          "6 books among 3 people is 6! = 6 x 5 x 4 x 3 x 2 x 1 = 720.",
          "In mathematics, factorization consists of writing a number or "
          "another mathematical object as a product of several factors, "
          "usually smaller or simpler objects of the same kind. Opposite of "
          "simplification (complication).",
          "Evaluate a mathematical expression.",
          "Converts a decimal number to a fraction.",
      };
      std::cout << "\nMath++ is a free and open-source tool created by "
                   "avighnac to solve math! For a full list of credits run "
                   "math++ credits.\nFUNCTIONS:\n";

      for (auto i = 0; i < functions.size(); i++) {
        if (is_windows()) {
          std::cout << "     -";
        } else
          std::cout << "     •";
        std::cout << functions[i] << "- " << function_definitions[i] << "\n";
      }

      std::cout
          << "\nNote: For help "
             "with any individual function run math++ [function] help.\n\n";
    }

    if (function == "credits") {
      TODO;
    }

    std::string version = "1.2.1";

    if (function == "check_update") {
      CURL *curl = curl_easy_init();
      if (!curl)
        throw std::runtime_error(
            "Error: curl_easy_init() failed while getting version.txt");
      curl_easy_setopt(curl, CURLOPT_URL,
                       "https://raw.githubusercontent.com/avighnac/math_new/"
                       "main/version.txt");
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_get_latest_version);
      curl_easy_perform(curl);
      curl_easy_cleanup(curl);
      replace_all(latest_version, "\n", "");
      if (latest_version == version)
        std::cout << "This version of math++ is up to date! (" << version
                  << ")\n";
      else
        std::cout << "This version of math++ is outdated.\n"
                  << "Current version: " << version << '\n'
                  << "Latest version: " << latest_version << '\n';
    }

    if (function == "version") {
      std::cout << "math++ version: " << version
                << " (released on 13-04-2022)\n";
      std::cout << "Tip: run math++ check_update to check if you have the "
                   "latest version of math++.\n";
    }

    if (function == "simple_interest" || function == "si") {
      if (argCount == 3) {
        std::string argument3 = argument[2];
        if (argument3 == "help")
          std::cout << "The function has a built-in help function. Why don't "
                       "you try using that? :) \n";
      } else {
        simpleInterest simpleInterest;
        simpleInterest.solve();
      }
    }

    if (function == "nroot") {
      if (argCount >= 5) {
        std::cout << nroot(std::string(argument[2]), std::string(argument[3]),
                           std::stoll(std::string(argument[4])));
      }
    }

    if (function == "factorial") {
      if (argCount >= 3) {
        std::string argument3 = argument[2];
        if (argument3 == "help")
          std::cout << "Syntax: math++ factorial [number] \n";
        else {
          std::string factorial = "1";
          long long number = std::stoll(argument3);
          for (long long i = 1; i < number + 1; i++)
            factorial =
                multiply(factorial, std::to_string(i));
          std::cout << factorial << "\n";
        }
      }
    }

    if (function == "fraction_simplifier" || function == "sf") {
      if (argCount == 2) {
        std::cout << "Fraction Simplifier (to help with your homework!) \n";
        std::cout << "Tip: Use math++ fraction_simplifier [numerator] "
                     "[denominator] to skip this interface. \n";
        long long numerator;
        long long denominator;
        std::cout << GREEN << "Numerator: " << RESET;
        std::cin >> numerator;
        std::cout << GREEN << "Denominator: " << RESET;
        std::cin >> denominator;

        std::pair<long long, long long> answer =
            fraction_simplifier({numerator, denominator});

        if (numerator == answer.first)
          std::cout << "Those two numbers are co-prime. \n";
        else
          std::cout << RED << numerator << "/" << denominator << RESET << " = "
                    << GREEN << answer.first << "/" << answer.second << "\n"
                    << RESET;
      }
      if (argCount == 3) {
        std::string argument3 = argument[2];
        if (argument3 == "help")
          std::cout << "Syntax: math++ fraction_simplifier [numerator] "
                       "[denominator] \n";
        else
          std::cout << "[math++.function.fraction_simplifier] Error: "
                       "Insufficient Arguments. \n";
      } else if (argCount >= 4) {
        long long numerator = std::stoll(argument[2]);
        long long denominator = std::stoll(argument[3]);

        std::pair<long long, long long> answer =
            fraction_simplifier({numerator, denominator});

        std::cout << answer.first << "/" << answer.second << "\n";
      }
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
            if (x & 1) {
              x++;
              number += "0";
            }

            std::string number_temp;
            for (auto &i : number)
              if (i != '.')
                number_temp.push_back(i);
            number = number_temp;

            bool i = false;
            std::string sqrt =
                integer_square_root(number, accuracy - (x / 2), i);
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
            std::cout << GREEN << "±" << RESET << sqrt << (i ? "i" : "")
                      << "\n";
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
            bool i = false;
            std::string square_root =
                integer_square_root(argument[2], accuracy, i);
            square_root.erase(0, std::min(square_root.find_first_not_of('0'),
                                          square_root.size() - 1));
            if (show_time)
              stop = std::chrono::high_resolution_clock::now();
            std::cout << GREEN << "±" << RESET << square_root << (i ? "i" : "")
                      << "\n";

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
                     "[num2] ... [numN] to skip this interface.\n\n";
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
          std::cout << "[math++.function.subtract] Error: Insufficient "
                       "Arguments! \n";
      } else if (argCount >= 4) {
        std::string answer = "0";

        for (auto i = 2; i < argCount; i++)
          answer = subtract(answer, argument[i]);

        std::cout << answer << "\n";
      }
    }

    if (function == "divide") {
      if (argCount == 2) {
        std::cout << "a/b\n"
                  << "    a = ";
        std::string a;
        std::cin >> a;
        std::cout << "    b = ";
        std::string b;
        std::cin >> b;
        std::cout << "    accuracy = ";
        int accuracy;
        std::cin >> accuracy;

        if (multiply(b, "1") != "0")
          std::cout << a << '/' << b << " = "
                  << color(divide(a, b, accuracy), "Green") << '\n';
        else
          std::cout << a << '/' << b << " is undefined.\n";
      } else if (argCount == 3) {
        if (std::string(argument[2]) == "help")
          std::cout << "Syntax: math++ divide [number-a] [number-b] [accuracy] "
                       "(answer will "
                       "be a/b)\n";
        else
          std::cout
              << "[math++.function.divide] Error: Missing second number.\n";
      } else if (argCount > 3) {
        int accuracy = std::max(std::string(argument[2]).length() * 3,
                                std::string(argument[3]).length() * 3);
        if (argCount > 4)
          accuracy = std::stoll(std::string(argument[4]));
        if (std::string(argument[3]) == "0") {
          std::cout << std::string(argument[2]) << "/"
                    << std::string(argument[3]) << " is undefined.\n";
        } else {
          auto quotient = divide(std::string(argument[2]),
                                 std::string(argument[3]), accuracy);
          std::cout << std::string(argument[2]) << "/"
                    << std::string(argument[3])
                    << (multiply(quotient, std::string(argument[3])) ==
                                multiply("1", std::string(argument[2]))
                            ? " = "
                            : " ≈ ")
                    << color(quotient, "Green") << std::endl;
        }
      }
    }

    /* if (function == "draw") {
     if (argCount < 3) {
       std::string argument3 = argument[2];
       if (argument3 == "help")
         std::cout << "Syntax: math++ draw [shape] [side1] ... [sideN] \n";
       else
         std::cout
             << "[math++.function.draw] Error: Insufficient Arguments! \n";
     }
     if (argCount >= 3) {
       std::string shape = argument[2];
       if (shape == "right_angled_triangle" ||
               shape == "right_angle_triangle" || shape == "90tri") {
         if (argCount >= 5) {
           std::vector<int> lengthSides;
           if (argCount >= 6) {
             lengthSides = {
                 std::stoi(argument[3]),
                 std::stoi(argument[4]),
                 std::stoi(argument[5]),
             };
           } else {
             lengthSides = {
                 std::stoi(argument[3]),
                 std::stoi(argument[4]),
                 (int)(std::sqrt(std::pow(std::stoi(argument[3]), 2) +
                                     std::pow(std::stoi(argument[4]), 2))),
             };
           }
           std::sort(lengthSides.begin(), lengthSides.end());
           int width = lengthSides[lengthSides.size() - 1];
           int height = lengthSides[lengthSides.size() - 2];
           cimg_library::CImg<unsigned int> image (width, height, 1, 3);
           image.fill(0xffffff);
           unsigned char black[3];
           black[0] = 255;
           black[1] = 255;
           black[2] = 255;
           for (auto i = 0; i < lengthSides[0]; i++)
             image.draw_point(0, height - i - 1, black);
           for (auto i = 0; i < lengthSides[1]; i++)
             image.draw_point(i, (height - 1), black);
           float ratio = (float)lengthSides[1] / (float) lengthSides[0];
           std::pair<float, int> start = {0, height - lengthSides[0]};
           std::pair<int, int> end = {lengthSides[1] - 1, lengthSides[1] - 1};
           std::pair<int, int> condition_pair;
           bool condition = true;
           while (condition_pair != end && condition_pair.second < end.second)
   { for (auto i = (int)start.first; i < ratio + (int)start.first; i++)
               image.draw_point(i, start.second, black);
             condition_pair = {(int)start.first, start.second};
             condition ? start.first =
                             start.first + ratio
                       : start.second++;
             condition = !condition;
           }
           image.normalize(0, 255);
           image.save("image.bmp");
         } else if (argCount == 3) {
           std::string fourthArgument = argument[3];
           if (fourthArgument == "help")
             std::cout << "Syntax: math++ draw right_angled_triangle [height]
   "
                          "[base] [optional: hypotenuse] \n";
           else std::cout << "[math.function.draw.right_angled_triangle] "
                               "Error: Insufficient "
                               "Sides! \n";
         }
       }
     }
   } */

    if (function == "multiply") {
      if (argCount == 3) {
        std::string argument3 = argument[2];
        if (argument3 == "help")
          std::cout << "Syntax: math++ multiply [num1] [num2] ... [numN] \n";
        else
          std::cout << "[math++.function.multiply] Error: Insufficient "
                       "Arguments! \n";
      }
      if (argCount >= 4) {
        std::string answer = "1";

        for (auto i = 2; i < argCount; i++)
          answer = multiply(answer, argument[i]);

        std::cout << answer << "\n";
      }
    }

    if (function == "evaluate") {

      bool debugPrint =
          (argCount >= 4 && std::string(argument[3]) == "-debugPrint");

      if (argCount == 2)
        std::cout << "Syntax: math++ evaluate [mathematical_expression]\n";
      if (argCount >= 3) {
        std::string sum = argument[2];

        sum.erase(std::remove(sum.begin(), sum.end(), ' '),
                  sum.end()); // Remove spaces
        while ((sum.find("--") != std::string::npos) ||
               (sum.find("++") != std::string::npos) ||
               (sum.find("-+") != std::string::npos) ||
               (sum.find("+-") != std::string::npos)) {
          replace_all(sum, "--", "+");
          replace_all(sum, "-+", "-");
          replace_all(sum, "+-", "-");
          replace_all(sum, "++", "+");
        }

        std::vector<algebric_num::algebric_number> nums =
            algebric_num::get_terms(sum, debugPrint);

        if (debugPrint)
          std::cout << '\n';

        for (auto i = 0; i < nums.size(); i++) { // Addition of like terms only
          for (auto j = i + 1; j < nums.size(); j++) {
            if (nums[i].variablePart == nums[j].variablePart) {
              algebric_num::algebric_number toPB("0");
              toPB.constantPart =
                  add(nums[i].constantPart, nums[j].constantPart);
              if (toPB.constantPart != "0" && toPB.constantPart != "-0" &&
                  toPB.constantPart != "+0")
                toPB.variablePart = nums[i].variablePart;
              algebric_num::erase_algebric_number(nums, i);
              j--;
              algebric_num::erase_algebric_number(nums, j);
              nums.push_back(toPB);
              j = i;
            }
          }
        }

        std::cout << algebric_num::convert_to_readable(nums)
                  << '\n'; // Printing out readable version.
      }
    }

    if (function == "is_prime") {
      if (argCount >= 3) {
        std::cout << "is_prime(" << argument[2]
                  << ") = " << (isPrime(std::string(argument[2])) ? "true" : "false")
                  << '\n';
      }
    }

    if (function == "factorize") {
      if (argCount >= 3) {
        if (std::string(argument[2]) == "help")
          std::cout << "Syntax: math++ factorize "
                       "[mathematical_expression]\n";
        else {
          bool debugPrint =
              (argCount >= 4 && std::string(argument[3]) == "-debugPrint");

          std::string sumString = argument[2];
          sumString.erase(std::remove(sumString.begin(), sumString.end(), ' '),
                          sumString.end()); // Remove spaces

          std::vector<algebric_num::algebric_number> terms =
              algebric_num::get_terms(sumString, debugPrint);

          std::string type;

          if (terms.size() == 3 &&
              (terms[0].variablePart ==
               algebric_num::asquare(terms[1]).variablePart) &&
              terms[2].variablePart.empty()) {
            type = "ax2bxc";
            
          } else if (terms.size() == 1 && terms[0].variablePart.empty()) {
            type = "primeFactor";
          }
          else {
            TODO;
            std::cout << "Tip: You can still try factorizing another type of "
                         "expression.\n";
            return 0;
          }

          if (debugPrint)
            std::cout << '\n';

          if (type == "ax2bxc") {
            std::cout << ax2bxc(sumString) << '\n';
            int accuracy = argCount == 5 ? std::stoi(argument[4]) : 8;
            std::cout << "Middle term split: "
                      << print_pair(split_middle_term_ax2bxc(
                             algebric_num::get_terms(sumString), accuracy))
                      << '\n';
          } else if (type == "primeFactor") {
            auto primeFactors = prime_factor::prime_factor(sumString);
            std::map<std::string, std::string> printable;
            std::string answer;
            for (auto &i : primeFactors) {
              if (printable.find(i.constantPart) == printable.end())
                printable.insert({i.constantPart, "1"});
              else
                printable.find(i.constantPart)->second = add(printable.find(i.constantPart)->second, "1");
            }
            for (auto &i : printable) {
              if (!algebric_num::smaller_than(algebric_num::algebric_number(i.second), algebric_num::algebric_number("2")))
                answer += i.first + "^" + i.second + " * ";
              else
                answer += i.first + " * ";
            }
            std::cout << answer.substr(0, answer.length() - 3);
          }
        }
      }
    }
    if (function == "deci_to_frac" || function == "dtf" ||
        function == "decimal_to_fraction") {
      if (argCount == 2) {
        std::cout << "Syntax: math++ decimal_to_fraction [decimal_number]\n";
      }
      if (argCount >= 3) {
        std::string decimal(argument[2]);
        std::string denominator = "1";
        while (decimal_point_exists(decimal)) {
          decimal = shift_decimal_point(decimal, 1);
          denominator += "0";
        }
        auto answer = fraction_simplifier({decimal, denominator});
        std::cout << GREEN << answer.first << "/" << answer.second << RESET
                  << '\n';
      }
    }
  }
}
