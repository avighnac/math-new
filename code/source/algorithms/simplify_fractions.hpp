#include "gcd.hpp"

std::pair<long long, long long> fraction_simplifier(std::pair<long long, long long> fraction) {
    long long hcf = gcd(fraction.first, fraction.second);
    return {fraction.first / hcf, fraction.second / hcf};
}