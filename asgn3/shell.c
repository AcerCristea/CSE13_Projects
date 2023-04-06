#include "shell.h"

#include "gaps.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    // array, length of array (amount of elements in the array)

    uint32_t j, temp;

    for (uint32_t gap = 0; gaps[gap] > 0; gap++) {
        //printf("getting the gap\n");
        for (uint32_t i = gap; i < length; i++) {
            //printf("comparing the elements\n");
            j = i;
            temp = arr[i];

            while (j >= gap && cmp(stats, temp, arr[j - gap]) == -1) { //temp < arr[j - gap]
                swap(stats, &arr[j], &arr[j - gap]);
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}
