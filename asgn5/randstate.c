#include "randstate.h"
#include <stdio.h>
#include <gmp.h>
#include <stdint.h>
#include "numtheory.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

gmp_randstate_t state;

//need to use random state initialization gmp

void randstate_init(uint64_t seed) {

    srandom(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed); // random seed in state
}

void randstate_clear(void) {

    gmp_randclear(state);
}
