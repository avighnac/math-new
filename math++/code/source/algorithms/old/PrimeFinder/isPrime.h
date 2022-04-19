#ifndef isPrime_h_
#define isPrime_h_

bool isPrime (long long x)
{
  if (!(x & 1))
    return false;

    long long i = 1;
    long long counter = 0;

    while (i <= x) {
      if (x % i == 0) {
        counter++;
          if (counter > 2)
            return false;
        }
        i++;
    }

    return counter == 2;
}

bool isPrime(std::string x) {
  if (!((x[x.length() - 1] - 48) & 1))
    return false;

  if (algebric_num::smaller_than(
          algebric_num::algebric_number(x),
          algebric_num::algebric_number("9223372036854775807")))
    return isPrime(std::stoll(x));

  std::string i = "1";
  std::string counter = "0";

  while (algebric_num::smaller_than(algebric_num::algebric_number(i),
                                    algebric_num::algebric_number(x))
                 || i == x) {
    if (modulus(x, i) == "0") {
      counter = add(counter, "1");
      if (algebric_num::greater_than(algebric_num::algebric_number(counter), algebric_num::algebric_number("2")))
        return false;
    }
    i = add(i, "1");
  }

  return counter == "2";
}

#endif