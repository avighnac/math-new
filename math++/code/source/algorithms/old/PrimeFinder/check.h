#ifndef check_h_
#define check_h_

#include "isDivisible.h"

bool check (long long number, const std::vector<long long>& vec) {
    for (auto i: vec) {
        if (isDivisible(number, i)) {
            return true;
        }
    }
    return false;
}

#endif