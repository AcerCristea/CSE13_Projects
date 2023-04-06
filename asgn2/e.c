#include "mathlib.h"

#include <stdio.h>

int static f = 0;

double e(void) {
    double n, term;
    n = 1.0; //approximation
    term = 1.0;
    double c;
    for (c = 1; term > EPSILON; c++) {
        term *= 1 / c; //creates the next term
        n += term; // adds the terms to the approx
    }

    f = c;

    return n;
}

int e_terms(void) {

    return f;
}
