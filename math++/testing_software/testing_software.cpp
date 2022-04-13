#include <chrono>
#include <iostream>
#include <map>

#include "../code/source/color.hpp"

#include "../code/source/algorithms/Addition Algorithm/add.hpp"
#include "../code/source/algorithms/Factorization/ax2bxc.hpp"
#include "../code/source/algorithms/integer_square_root.hpp"
#include "../code/source/algorithms/modulus.hpp"

bool choiceHandler(std::string choice) {
  if (choice == "add") {
    std::cout << "Testing add.hpp.\n";
    std::cout << color("basic_test_set (check if function works)\n", "Cyan");

    std::map<std::pair<std::string, std::string>, std::string> testSet1;
#include "tests/add/test_set_1"

    std::string tab = "  ";
    int count = 0;
    bool functionDoesNotWork = false;
    bool failedHugeNumbers = false;
    auto start = std::chrono::high_resolution_clock::now();
    for (auto &i : testSet1) {
      if (add(i.first.first, i.first.second) == i.second) {
        std::cout << "\33[2K\r" << tab
                  << color("Test " + std::to_string(count + 1) + " Passed. [" +
                               std::to_string(count + 1) + "/6]",
                           "Green");
      } else {
        std::cout << "\33[2K\r" << tab
                  << color("Test " + std::to_string(count + 1) + " Failed. [" +
                               std::to_string(count + 1) + "/6]",
                           "Red");
        functionDoesNotWork = true;
        break;
      }

      count++;
    }

    count = 0;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\n  Time taken: "
              << color(
                     std::to_string(
                         std::chrono::duration_cast<std::chrono::milliseconds>(
                             end - start)
                             .count()),
                     "Magenta")
              << color("ms.", "Magenta");
    if (!functionDoesNotWork) {
      std::cout << '\n';
      std::cout << color("bigger_numbers (50 digits per number)", "Cyan");
      std::cout << '\n';

      std::map<std::pair<std::string, std::string>, std::string> testSet2;
#include "tests/add/test_set_2"

      bool failedTestSet2 = false;
      start = std::chrono::high_resolution_clock::now();
      for (auto &i : testSet2) {
        std::string answer = add(i.first.first, i.first.second);
        if (answer == i.second) {
          std::cout << "\33[2K\r" << tab
                    << color("Test " + std::to_string(count + 1) +
                                 " Passed. [" + std::to_string(count + 1) +
                                 "/50]",
                             "Green");
        } else {
          std::cout << "\33[2K\r" << tab
                    << color("Test " + std::to_string(count + 1) +
                                 " Failed. [" + std::to_string(count + 1) +
                                 "/50]",
                             "Red");
          failedTestSet2 = true;
          break;
        }
        count++;
      }

      count = 0;
      end = std::chrono::high_resolution_clock::now();
      std::cout
          << "\n  Time taken: "
          << color(std::to_string(
                       std::chrono::duration_cast<std::chrono::milliseconds>(
                           end - start)
                           .count()),
                   "Magenta")
          << color("ms.", "Magenta");

      if (!failedTestSet2) {
        std::cout << '\n';
        std::cout << color("very_huge_numbers (1000 digits per number)",
                           "Cyan");
        std::cout << '\n';

        std::map<std::pair<std::string, std::string>, std::string> testSet3;
#include "tests/add/test_set_3"

        start = std::chrono::high_resolution_clock::now();
        for (auto &i : testSet3) {
          std::string answer = add(i.first.first, i.first.second);
          if (answer == i.second) {
            std::cout << "\33[2K\r" << tab
                      << color("Test " + std::to_string(count + 1) +
                                   " Passed. [" + std::to_string(count + 1) +
                                   "/5]",
                               "Green");
          } else {
            std::cout << "\33[2K\r" << tab
                      << color("Test " + std::to_string(count + 1) +
                                   " Failed. [" + std::to_string(count + 1) +
                                   "/5]",
                               "Red");
            failedHugeNumbers = true;
            break;
          }
          count++;
        }

        count = 0;
        end = std::chrono::high_resolution_clock::now();
        std::cout
            << "\n  Time taken: "
            << color(std::to_string(
                         std::chrono::duration_cast<std::chrono::milliseconds>(
                             end - start)
                             .count()),
                     "Magenta")
            << color("ms.", "Magenta");
      }
    }

    if (!failedHugeNumbers) {
      // passed all
      std::cout << '\n';
      return true;
    }
  }
  if (choice == "sqrt") {
    bool passed = true;
    std::map<std::string, std::string> test_set_1;
    std::cout << "Testing integer_square_root.hpp." << '\n';
    std::cout << color("integer_square_root", "Yellow") << "(n = (\""
              << color("0", "Magenta") << "\" → \"" << color("199", "Magenta")
              << "\"), " << color("25", "Magenta") << ")\n";
#include "tests/sqrt/test_set_1"
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 0; i < 200; i++) {
      if (integer_square_root(std::to_string(i), 25) ==
          test_set_1.find(std::to_string(i))->second)
        std::cout << "\33[2K\r"
                  << color("  Test " + std::to_string(i + 1) + " passed. [" +
                               std::to_string(i + 1) + "/" + "200]",
                           "Green")
                  << std::flush;
      else {
        std::cout << "\33[2K\r"
                  << color("  Test " + std::to_string(i + 1) + " failed. [" +
                               std::to_string(i + 1) + "/" + "200]",
                           "Red");
        std::cout << " a.k.a "
                  << color("integer_square_root(\"" + std::to_string(i) +
                               "\", " + "25)",
                           "Red")
                  << "\n";
        std::cout << "    →  Expected: "
                  << color(test_set_1.find(std::to_string(i))->second, "Green");
        std::cout << "\n    →  Actual: "
                  << color(integer_square_root(std::to_string(i), 25), "Red")
                  << '\n';
        passed = false;
        break;
      }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\n  Time taken: "
              << color(
                     std::to_string(
                         std::chrono::duration_cast<std::chrono::milliseconds>(
                             end - start)
                             .count()),
                     "Magenta")
              << color("ms.", "Magenta");
    return passed;
  }
  if (choice == "factorize") {
    bool passed = true;
    std::cout << "Testing ax2bxc.hpp.\n";
    std::map<std::string, std::string> test_set_1;
#include "tests/factorize/test_set_1"

    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;
    for (auto &i : test_set_1) {
      if (ax2bxc(i.first) == i.second) {
        std::cout << "\33[2K\r"
                  << color("  Test " + std::to_string(count + 1) +
                               " passed. [" + std::to_string(count + 1) + "/" +
                               std::to_string(test_set_1.size()) + "]",
                           "Green")
                  << std::flush;
      } else {
        std::cout << "\33[2K\r"
                  << color("  Test " + std::to_string(count + 1) +
                               " failed. [" + std::to_string(count + 1) + "/" +
                               std::to_string(test_set_1.size()) + "]",
                           "Red")
                  << std::flush;
        std::cout << " a.k.a " << color("ax2bxc(\"" + i.first + "\")", "Red")
                  << "\n";
        std::cout << "    →  Expected: "
                  << color("\"" + i.second + "\"", "Green");
        std::cout << "\n    →  Actual: "
                  << color("\"" + ax2bxc(i.first) + "\"", "Red") << '\n';
        passed = false;
        break;
      }
      count++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\n  Time taken: "
              << color(
                     std::to_string(
                         std::chrono::duration_cast<std::chrono::milliseconds>(
                             end - start)
                             .count()),
                     "Magenta")
              << color("ms.", "Magenta");
    return passed;
  }
  if (choice == "modulus") {
    bool passed = true;
    std::string totalTests = "10000";
    int currentTest;
    std::cout << "Testing modulus.hpp.\n";
    auto start = std::chrono::high_resolution_clock::now();
    for (auto i = 1; i < 101; i++) {
      if (!passed)
        break;
      for (auto j = 1; j < 101; j++) {
        currentTest++;
        if (std::to_string(i % j) ==
            modulus(std::to_string(i), std::to_string(j))) {
          std::cout << "\33[2K\r"
                    << color("  Test " + std::to_string(currentTest) +
                                 " passed. [" + std::to_string(currentTest) +
                                 "/" + totalTests + "]",
                             "Green")
                    << std::flush;
        } else {
          std::cout << "\33[2K\r"
                    << color("  Test " + std::to_string(currentTest) +
                                 " failed. [" + std::to_string(currentTest) +
                                 "/" + totalTests + "]",
                             "Red")
                    << std::flush;
          std::cout << " a.k.a "
                    << color("modulus(\"" + std::to_string(i) + "\", \"" +
                                 std::to_string(j) + "\")",
                             "Red")
                    << "\n";
          std::cout << "    →  Expected: "
                    << color(std::to_string(i % j), "Green");
          std::cout << "\n    →  Actual: "
                    << color(modulus(std::to_string(i), std::to_string(j)),
                             "Red")
                    << '\n';
          passed = false;
          break;
        }
      }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "\n  Time taken: "
              << color(
                     std::to_string(
                         std::chrono::duration_cast<std::chrono::milliseconds>(
                             end - start)
                             .count()),
                     "Magenta")
              << color("ms.", "Magenta");
    return passed;
  }
  return false;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
#if defined(_WIN32)
    std::cout
        << "Since you're on windows, colored text won't be displayed. \n\n";
#endif

    std::cout << color("--------", "Blue") << color(" Math++ ", "Yellow")
              << color("Official ", "Magenta")
              << color("Testing Software ", "Cyan") << color("--------", "Blue")
              << "\n\n";

    bool add = choiceHandler("add");
    std::cout << "\n";
    bool sqrt = choiceHandler("sqrt");
    std::cout << "\n\n";
    bool factorize = choiceHandler("factorize");
    std::cout << "\n\n";
    bool modulus = choiceHandler("modulus");

    std::cout << "\n\nSummary: ";
    if (add && sqrt && factorize && modulus) {
      std::cout << color("Passed all tests.\n", "Green");
      return 0;
    } else {
      throw std::runtime_error("Failed some tests.\n");
      return 1;
    }

  } else if (argc >= 2) {
    std::cout << "\033[A\33[2K\r";
    choiceHandler(std::string(argv[1]));
  }
}