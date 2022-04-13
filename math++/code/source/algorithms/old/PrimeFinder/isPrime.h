#ifndef isPrime_h_
#define isPrime_h_

bool isPrime (int x)
{
    int i = 1;
    int counter = 0;

    while (i < x  + 1) {
        if (isDivisible(x, i) == 1) {
                counter++;
          if (counter > 2)
            return false;
        }
        i++;
    }

    if (counter == 2) {
        return true;
    } else {
        return false;
    }
}

bool isPrime(std::string x) {
  if (algebric_num::smaller_than(
          algebric_num::algebric_number(x),
          algebric_num::algebric_number("9223372036854775807")))
    return isPrime(std::stoll(x));

  std::string i = "1";
  std::string counter = "0";

  while (algebric_num::smaller_than(algebric_num::algebric_number(i),
                      algebric_num::algebric_number(add(x, "1")))) {
    if (isDivisible(x, i) == true) {
      counter = add(counter, "1");
      if (algebric_num::greater_than(algebric_num::algebric_number(counter), algebric_num::algebric_number("2")))
        return false;
    }
    i = add(i, "1");
  }

  if (counter == "2") {
    return true;
  } else {
    return false;
  }
}

#endif