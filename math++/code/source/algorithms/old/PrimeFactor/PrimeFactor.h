#ifndef PrimeFactor_h_
#define PrimeFactor_h_

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <iterator>

#include "../PrimeFinder/noteqcheck.h"
#include "../PrimeFinder/isDivisible.h"
#include "../PrimeFinder/check.h"
#include "../PrimeFinder/isPrime.h"

std::vector<long long> primeFactor(long long toPF)
{
    std::vector<long long> lsColumn;

    if (isPrime(toPF)) {
        std::vector<long long> answer;
        answer.push_back(toPF);
        answer.push_back(1);
        return answer;
    } else {
        long long range1 = 1;
        long long range2 = toPF/2;

        long long i = range1;
        long long counter = 0;
        std::vector<long long> prime;
        std::vector<long long> primers;

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
                        primers.push_back(i);
                        counter++;
                    }
                }
            } else {
                if (isPrime(i) == 1) {
                    primers.push_back(i);
                    counter++;
                }
            }
            i++;
        }
        long long* primeNumbers = new long long[primers.size()];
        for (auto i = 0; i < primers.size(); i++)
            primeNumbers[i] = primers[i];

        std::ostringstream answer;
        auto check = toPF;

        while (toPF != 1) {
            for (auto i = 0; counter > i; i++) {
                if (toPF % primeNumbers[i] == 0) {
                    lsColumn.push_back(primeNumbers[i]);
                    toPF = toPF / primeNumbers[i];
                }
            }
        }
        long long test = 1;
        for (auto i = 0; i < lsColumn.size(); i++) {
            test = test * lsColumn[i];
        }

        if (!lsColumn.empty()) {
            return lsColumn;
        }
    }
    return lsColumn;
}

#endif
