#ifndef isDivisible_h_
#define isDivisible_h_

bool isDivisible(int divident, int divisor)
{
    if (divident % divisor == 0)
        return true;
    else
        return false;
}

#endif