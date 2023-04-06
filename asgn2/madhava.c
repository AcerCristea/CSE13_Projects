#include "mathlib.h"

#include <stdio.h>

int static f = 0.0;

double pi_madhava(void) {

    double top_v, bot_v, term, answer, n, three, k;

    top_v = 0.0;
    bot_v = 0.0;
    three = 1.0;
    term = 1.0;
    n = 0.0;

    for (k = 0; absolute(term) > EPSILON; k++) {
        f++;
        top_v = 1 / three;

        bot_v = (2 * k) + 1;

        term = top_v / bot_v;
        three *= -3;
        n += term;
        //multiply by previous step to get to the power of
    }

    answer = (n * sqrt_newton(12));

    return answer;
}

int pi_madhava_terms(void) {
    return f;
}
