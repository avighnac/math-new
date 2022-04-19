#ifndef isPrime_h_
#define isPrime_h_

std::vector<long long> primeNumbers = {
    2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,
    41,  43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,
    97,  101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151,
    157, 163, 167, 173, 179, 181, 191, 193, 197, 199};

bool isPrime(long long x) {
  for (auto &i : primeNumbers)
    if (x != i && x % i == 0)
      return false;

  if (x == 2 || x == 3)
    return true;

  if (x <= 1 || (!(x & 1)) || x % 3 == 0)
    return false;

  for (long long i = 5; i * i <= x; i += 6)
    if (x % i == 0 || x % (i + 2) == 0)
      return false;

  return true;
}

bool isPrime(std::string x, bool testing = false) {
  if (multiply(x, "1") == "2")
    return true;

  if (!((x[x.length() - 1] - 48) & 1))
    return false;

  if (!testing)
    if (algebric_num::smaller_than(
            algebric_num::algebric_number(x),
            algebric_num::algebric_number("9223372036854775807")))
      return isPrime(std::stoll(x));

  std::string i = "1";
  int counter = 0;

  while (algebric_num::smaller_than(algebric_num::algebric_number(i),
                                    algebric_num::algebric_number(x)) ||
         i == x) {
    if (modulus(x, i) == "0") {
      counter++;
      if (counter > 2)
        return false;
    }
    i = add(i, "1");
  }

  return counter == 2;
}

#endif