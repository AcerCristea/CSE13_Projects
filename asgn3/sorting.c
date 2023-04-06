#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h> // for PRIu32
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // using getopt()

#define OPTIONS "Hasbhqn:p:r:"

typedef enum { SHELL, BATCHER, HEAP, QUICK } Sorts;

void p_element(
    uint32_t *arr, uint32_t elem) { // for case p: prints the elements for the sorting functions
    for (uint32_t i = 0; i < elem; i++) {
        if (i % 5 == 0) {
            printf("\n");
        }
        if (arr[i] == 0) {
            break;
        }
        printf("%13" PRIu32, arr[i]);
    }
    printf("\n");
}

int main(int argc, char **argv) {

    char *func_name[] = { "Shell Sort", "Batcher Sort", "Heap Sort", "Quick Sort" };

    uint32_t size = 100; // default
    uint32_t seed = 13371453; // default
    uint32_t elem = 100; // default

    uint32_t *sizeptr = &size;
    uint32_t *seedptr = &seed;
    uint32_t *elemptr = &elem;

    int opt = 0;
    Set s = set_empty(); // initalizes empty set
    Stats stats; // initalizes stats to use
    reset(&stats);

    stats.moves = 0;
    stats.compares = 0;

    if (size < elem) { // prints specified elements instead of all
        elem = size;
    }

    bool case_a = false;
    bool case_s = false;
    bool case_b = false;
    bool case_q = false;
    bool case_h = false;
    bool case_r = false;
    bool case_n = false;
    bool case_p = false;
    bool case_H = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {

        case 'a': // employs all sorting algorithms
            //printf("entering case a\n");
            s = set_insert(s, SHELL);
            s = set_insert(s, BATCHER);
            s = set_insert(s, HEAP);
            s = set_insert(s, QUICK);
            case_a = true;
            break;

        case 's': // enables shell sort
            //printf("entering case s\n");
            s = set_insert(s, SHELL);
            case_s = true;
            break;

        case 'b': // enables batcher sort
            //printf("entering case s\n");
            s = set_insert(s, BATCHER);
            case_b = true;
            break;

        case 'q': // enables quick sort
            //printf("entering case q\n");
            s = set_insert(s, QUICK);
            case_q = true;
            break;

        case 'h': // enables heap sort
            //printf("entering case h\n");
            s = set_insert(s, HEAP);
            case_h = true;
            break;

        case 'r': // seed
            if (strtoll(optarg, NULL, 10) > 0 && strtoll(optarg, NULL, 10) < 10000000000) {

                *seedptr = strtoull(optarg, NULL, 10); // seed
                srandom(strtoull(optarg, NULL, 10));
            } else {
                printf("error: intput not in range 0 - 10,000,000,000\n");
                exit(1);
            }
            case_r = true;
            break;

        case 'n': // number of elements
            if (atoi(optarg) >= 1 && atoi(optarg) <= 250000000) {
                *sizeptr = atoi(optarg);
            } else {
                printf("error: input not in range 1 - 250,000,000\n");
                exit(1);
            }
            case_n = true;
            break;

        case 'p': // print out elements from the array
            *elemptr = atoi(optarg);
            break;

        case 'H': // print out program usage
            printf("Select at least one sort to perform\nSYNOPSIS\n   A collection of "
                   "comparison-based sorting algorithms.\n\nUSAGE \n   ./sorting [-Hasbhqn:p:r:] "
                   "[-n length] [-p elements] [-r seed]\n\n");

            printf(
                "OPTIONS\n   -H\t\tDisplay program help and usage.\n   -a\t\tEnable all sorts.\n   "
                "-s\t\tEnable Shell Sort.\n   -b\t\tEnable Batcher Sort.\n   -h\t\tEnable Heap "
                "Sort.\n   -q\t\tEnable Quick Sort.\n   -n length\tSpecify number of array elemnts "
                "(default: 100).\n   -p elements\tSpecify number of elements to print (default: "
                "100).\n   -r seed\tSpecify random seed (default: 13371453).\n");
            case_h = true;
            return 1;
        }
    }

    if ((case_H == false) && (case_a == false) && (case_s == false) && (case_b == false)
        && (case_h == false) && (case_q == false) && (case_n == false) && (case_p == false)
        && (case_r == false)) {

        printf("Select at least one sort to perform\nSYNOPSIS\n   A collection of comparison-based "
               "sorting algorithms.\n\nUSAGE \n   ./sorting [-Hasbhqn:p:r:] [-n length] [-p "
               "elements] [-r seed]\n\n");

        printf("OPTIONS\n   -H\t\tDisplay program help and usage.\n   -a\t\tEnable all sorts.\n   "
               "-s\t\tEnable Shell Sort.\n   -b\t\tEnable Batcher Sort.\n   -h\t\tEnable Heap "
               "Sort.\n   -q\t\tEnable Quick Sort.\n   -n length\tSpecify number of array elemnts "
               "(default: 100).\n   -p elements\tSpecify number of elements to print (default: "
               "100).\n   -r seed\tSpecify random seed (default: 13371453).\n");
    }

    int size_set = 4;
    for (int n = 0; n <= size_set - 1; n++) {
        srandom(seed);
        uint32_t *array = (uint32_t *) calloc(size, sizeof(uint32_t));
        // array for each function to sort

        for (uint32_t i = 0; i < size; i++) {
            array[i] = random() & 0x3FFFFFFF; // bit masking to 30
        }

        if (set_member(s, n)) {
            reset(&stats);
            if (n == 0) {
                shell_sort(&stats, array, size);
            }

            if (n == 1) {
                batcher_sort(&stats, array, size);
            }

            if (n == 2) {
                heap_sort(&stats, array, size);
            }
            if (n == 3) {
                quick_sort(&stats, array, size);
            }

            printf("%s, %u elements, %lu moves, %lu compares\n", func_name[n], size, stats.moves,
                stats.compares);

            p_element(array, elem);
            reset(&stats);
        }
        free(array);
    }
    return 0;
}
