#include "mathlib.h"

#include <stdio.h>

int static f = 0.0;

double pi_bbp(void) {

    double top_v, bot_v, term, n, mult, k, sixteen;

    sixteen = 1.0;
    top_v = 0.0;
    bot_v = 0.0;
    term = 1.0;
    n = 0.0;

    for (k = 0; absolute(term) > EPSILON; k++) {
        f++;
        mult = 1 / sixteen;
        top_v = (k * (120 * k + 151) + 47);

        bot_v = k * (k * (k * (512 * k + 1024) + 712) + 194) + 15;

        term = mult * (top_v / bot_v);
        sixteen *= 16;
        n += term;
        //multiply by previous step to get to the power of
    }

    return n;
}

int pi_bbp_terms(void) {
    return f;
}
