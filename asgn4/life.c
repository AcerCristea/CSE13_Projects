#include "universe.h"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// for ncursers

#define DELAY 50000

#define OPTIONS "tsn:i:o:"

int main(int argc, char **argv) {

    uint32_t gens = 100; //default

    char *input = NULL;
    char *output = NULL;

    int opt = 0;

    uint32_t *gen_ptr = &gens;

    bool case_s = false;

    bool T = false;

    // 1. parse the command-line function
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {

        case 't': T = true; break;

        case 's':
            //nothing should be displayed by ncurses
            //goes straight to the print function
            case_s = true;
            break;

        case 'n':
            //specifies number of generations defauly(100)
            *gen_ptr = atoi(optarg);
            break;

        case 'i':
            input = optarg;
            //specifies the input file to read in order to populate universe
            break;

        case 'o': output = optarg; break;
        }
    } // outside while loop

    // 2. use an initial call to fscanf()
    //generation is one iteration of game of life

    FILE *infile = stdin; // default input file
    FILE *ofile = stdout; //default output file

    // opens input file if it exists
    if (input != NULL) {
        infile = fopen(input, "r");
    }

    uint32_t r;
    uint32_t c;

    fscanf(infile, "%u %u", &r, &c);

    // 3. create two universes using the dimensions obtained by fscanf()
    //    mark the universes toroidal if the t option was specifed
    Universe *A = uv_create(r, c, T);

    Universe *B = uv_create(r, c, T);

    Universe *temp = uv_create(r, c, T); // placeholder for swapping

    // 4. populate universe A with the remainder of the input
    uv_populate(A, infile);

    // 5. setup ncurses screen -------------------------------- wrong
    if (case_s == false) {
        initscr(); // Initialize the screen.
        curs_set(FALSE); // Hide the cursor.
    }

    // 6. For each generation up to the set number of generations:
    for (uint32_t gen = 0; gen < gens; gen++) {

        // a) if ncurses isn't silenced by the -s option...
        if (case_s == false) {
            refresh();
            usleep(DELAY);
            clear();
        }

        // b) perform one generation:
        for (uint32_t row = 0; row < uv_rows(A); row++) {
            for (uint32_t col = 0; col < uv_cols(A); col++) {

                uint32_t neighboor = uv_census(A, row, col); // census of each cell in universe A
                //printf("neighbor: %u\n", neighboor);
                bool cell = uv_get_cell(A, row, col); // checks to see if its live or not

                if ((cell == false) && (neighboor == 3)) {

                    uv_live_cell(B, row, col);

                    if (case_s == false) {

                        mvprintw(row, col, "o");
                    }

                }

                else if ((cell == true) && (neighboor == 2 || neighboor == 3)) {

                    uv_live_cell(B, row, col);

                    if (case_s == false) {

                        mvprintw(row, col, "o");
                    }
                }

                else {
                    uv_dead_cell(B, row, col);
                }
            }
        }

        // c) swap the universes:
        temp = A;
        A = B;
        B = temp;
    } // outside of main for loop

    // 7. close the screen with endwin()
    endwin();

    if (output != NULL) {
        ofile = fopen(output, "w");
    }

    uv_print(A, ofile);

    // 8. output universe A to specified file using uv_print()

    return 0;
}
