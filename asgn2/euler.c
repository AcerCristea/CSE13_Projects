#include "mathlib.h"

#include <stdio.h>

int static f;

double pi_euler(void) {
    double c, n, term, answer;
    n = 0.0; //approximation
    term = 1.0;

    for (c = 1; term > EPSILON; c++) {
        f++;
        term = 1 / (c * c); //creates the next term
        //printf("term: %f\n", term);
        n += term; // adds the terms to the approx
        //printf("n: %f\n", n);
    }

    answer = sqrt_newton(6 * n);

    return answer;
}

int pi_euler_terms(void) {

    return f;
}
