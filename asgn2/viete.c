#include "mathlib.h"

#include <stdio.h>

int static f = 0.0;

double pi_viete(void) {

    double top_v, bot_v, term, n, k, pre_v;

    top_v = sqrt_newton(2); // numrerator
    bot_v = 2.0; // denominator
    term = top_v / bot_v; // first term
    n = 1.0; // approximation

    for (k = 1; absolute(term) < 1; k++) {
        f++;

        n *= term; // updates approximation

        pre_v = top_v; // saves state of last numerator

        top_v = sqrt_newton(pre_v + 2); // makes new numerator

        term = (top_v / bot_v); // creates next term

        //multiply by previous step to get to the power of
    }

    return 2 / n;
}

int pi_viete_factors(void) {
    return f;
}
