#ifndef isPrime_h_
#define isPrime_h_

bool isPrime (int x)
{
    int i = 1;
    int counter = 0;

    while (i < x  + 1) {
        if (isDivisible(x, i) == 1) {
                counter++;
        }
        i++;
    }

    if (counter == 2) {
        return true;
    } else {
        return false;
    }
}


#endif