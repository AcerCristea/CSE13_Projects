#include "batcher.h"

#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {

    if (cmp(stats, A[x], A[y]) == 1) {
        swap(stats, &A[x], &A[y]);
    }
}

void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {

    if (n == 0) {

        return;
    }

    uint32_t c = 0;

    for (uint32_t t = n / 2; t > 0; c++) {
        t = t / 2; // continously prints 5 10/2,

        //printf("t %u\n", t);
    } //Until the number I'm deividing is zero
    c += 1;
    //printf("c %u\n",c);
    uint32_t p = 1 << (c - 1);

    while (p > 0) {

        uint32_t q = 1 << (c - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            for (uint32_t i = 0; (i < (n - d)); i++) {
                if ((i & p) == r) {

                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
