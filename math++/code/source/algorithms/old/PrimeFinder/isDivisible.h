#ifndef isDivisible_h_
#define isDivisible_h_

bool isDivisible(int divident, int divisor)
{
  return (divident % divisor == 0);
}

bool isDivisible(std::string divident, std::string divisor)
{
  return (modulus(divident, divisor) == "0");
}

#endif