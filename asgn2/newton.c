#include "mathlib.h"

#include <stdio.h>

int static f = 0;

double sqrt_newton(double x) {

    double z = 0.0;
    double y = 1.0;
    double c = 0.0;

    while (absolute(y - z) > EPSILON) {
        c++;
        z = y;
        y = 0.5 * (z + x / z);
    }
    f = c;
    return y;
}

int sqrt_newton_iters(void) {
    return f;
}
