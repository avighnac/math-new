#ifndef PrimeFinder_h_
#define PrimeFinder_h_

#include "check.h"
#include "isPrime.h"
#include "noteqcheck.h"
#include "isDivisible.h"

void PrimeFinder(int range1, int range2, std::string fifthArg) {
    int i = range1;
    int counter = 0;
    std::vector<int> prime;
    std::string answer;

    prime.push_back(2);
    prime.push_back(3);
    prime.push_back(5);
    prime.push_back(7);
    prime.push_back(11);
    prime.push_back(13);
    prime.push_back(17);
    prime.push_back(19);
    prime.push_back(23);
    prime.push_back(29);
    prime.push_back(31);

    while (i < range2+1) {
        if (!noteqcheck(i, prime)) {
            if (!check(i, prime)) {
                if (isPrime(i) == 1) {
                    if (fifthArg == "--comma") {
                        answer += (std::to_string(i) + ", ");
                    } else {
                        answer += (std::to_string(i) + " ");
                    }
                    //prime.push_back(i);
                    counter++;
                }
            }
        } else {
            if (isPrime(i) == 1) {
                if (fifthArg == "--comma") {
                    answer += (std::to_string(i) + ", ");
                } else {
                    answer += (std::to_string(i) + " ");
                }
                //prime.push_back(i);
                counter++;
            }
        }
        i++;
    }
    if (answer[answer.length()-2] == ',') answer = answer.substr(0, answer.length()-2);
    std::cout << answer << std::endl;
    std::cout << std::endl << std::endl << "There are " << counter << " Prime Number/s between " << range1 << " and " << range2 << "." << std::endl;
}

#endif // PrimeFinder_h_
