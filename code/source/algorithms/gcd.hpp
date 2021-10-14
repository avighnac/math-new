#include <vector>

long long
gcd(const long long &a,
    const long long &b) { /*Takes two numbers as
                        input and outputs their GCD.*/
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

long long
gcd(std::vector<long long> numbers) { /*Takes an array as input and outpots GCD
                                         of all array elements.*/
  if (numbers.empty())
    return -1;
  long long &first = numbers[0];
  for (auto i = 1; i < numbers.size(); i++)
    first = gcd(first, numbers[i]);

  return first;
}