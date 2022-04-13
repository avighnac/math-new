#include <iostream>
#include <string>
#include <time.h>

#include "code/source/algorithms/Addition Algorithm/add.hpp"

int main() {
    srand(time(0));

    for (auto i = 0; i < 5; i++) {
        std::string num1, num2, result;
        for (auto j = 0; j < 150; j++) {        
            num1 += std::to_string(rand() % 11);
            num2 += std::to_string(rand() % 11);
        }
    result = add(num1, num2);
    std::cout << "testSet3.insert({{\"" << num1 << "\", \"" << num2 << "\"}, \"" << result << "\"});\n" ;
    }
}