#include <limits.h>
#include <stdio.h>

unsigned long max_value(unsigned nchars) {
    if(nchars * CHAR_BIT > sizeof(unsigned long) * CHAR_BIT || nchars == 0) {
        return 0;
    }
    unsigned long res = 1UL << ((nchars * CHAR_BIT) - 1);

    return res - 1;
}