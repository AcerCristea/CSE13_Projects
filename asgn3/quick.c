#include "quick.h"

#include "stats.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t partition(Stats *stats, uint32_t *A, uint32_t lo, uint32_t hi) {

    uint32_t i = lo - 1;

    for (uint32_t j = lo; j < hi; j++) {

        if (cmp(stats, A[j - 1], A[hi - 1]) == -1) {

            i += 1;
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}

void quick_sorter(Stats *stats, uint32_t *A, uint32_t low, uint32_t high) {

    if (low < high) {

        uint32_t p = partition(stats, A, low, high); // this line wrong

        quick_sorter(stats, A, low, p - 1);
        quick_sorter(stats, A, p + 1, high);
    }
}

void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {

    quick_sorter(stats, A, 1, n);
}
