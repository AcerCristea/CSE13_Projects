#include "universe.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {

    // allocate the space in memory for the universe
    Universe *uv = (Universe *) malloc(sizeof(Universe));

    // allocate the grid
    uv->grid = (bool **) calloc(rows, sizeof(bool *));
    for (uint32_t r = 0; r < rows; r += 1) {
        uv->grid[r] = (bool *) calloc(cols, sizeof(bool));
    }

    // set toroidal to the uv->toroidal
    uv->toroidal = toroidal;
    uv->rows = rows;
    uv->cols = cols;

    // return the universe
    return uv;
}

void uv_delete(Universe *u) {

    //how to iterate through the arrays and free each cell
    //free grid as a whole
    for (uint32_t r = 0; (r < u->rows); r++) {

        free(u->grid[r]);

        for (uint32_t c = 0; c < u->cols; c++) {

            free(u->grid[c]);
        }
    }
}

uint32_t uv_rows(Universe *u) {
    //accessor function

    return u->rows;
}

uint32_t uv_cols(Universe *u) {

    return u->cols;
}

void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {

    //marks the cell at row r and col c as live, grid bool variable true

    if ((r <= u->rows) && (c <= u->cols)) {

        u->grid[r][c] = true;
    }
}

void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {

    u->grid[r][c] = false;
}

bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {

    if ((r <= u->rows) && (c <= u->cols) && (u->grid[r][c] == true)) {

        // printf("r: %u, c: %u\n", r, c);

        return true;
    }

    else {

        return false;
    }
}

bool uv_populate(Universe *u, FILE *infile) {

    uint32_t r;
    uint32_t c;
    while (!feof(infile)) {

        int scan = fscanf(infile, "%u %u", &r, &c);

        if (scan == -1) {

            return true;
        }

        if ((r <= u->rows) && (c <= u->cols)) {

            //       printf("r: %u, c: %u\n",r,c);

            uv_live_cell(u, r, c);

            //u->grid[r][c] = true;

        }

        else {

            printf("Failure to populate universe");
            return false;
            break;
        }
    }
    return true;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {

    uint32_t track = 0;

    if (u->toroidal == false) {

        if ((r + 1 <= u->rows - 1) && (c <= u->cols - 1) && (u->grid[r + 1][c] == true)) {

            //	printf("down\n");
            track += 1;
        }

        if ((r <= u->rows - 1) && (c + 1 <= u->cols - 1) && (u->grid[r][c + 1] == true)) {
            //	printf("right\n");
            track += 1;
        }

        if ((r - 1 <= u->rows - 1) && (c <= u->cols - 1) && (u->grid[r - 1][c] == true)) {
            //	printf("up\n");
            track += 1;
        }

        if ((r <= u->rows - 1) && (c - 1 <= u->cols - 1) && (u->grid[r][c - 1] == true)) {
            //	printf("left\n");
            track += 1;
        }

        if ((r + 1 <= u->rows - 1) && (c + 1 <= u->cols - 1) && (u->grid[r + 1][c + 1] == true)) {
            //	printf("bottom right\n");
            track += 1;
        }

        if ((r - 1 <= u->rows - 1) && (c - 1 <= u->cols - 1) && (u->grid[r - 1][c - 1] == true)) {
            //	printf("top left\n");
            track += 1;
        }

        if ((r - 1 <= u->rows - 1) && (c + 1 <= u->cols - 1) && (u->grid[r - 1][c + 1] == true)) {
            //	printf("top right\n");
            track += 1;
        }

        if ((r + 1 <= u->rows - 1) && (c - 1 <= u->cols - 1) && (u->grid[r + 1][c - 1] == true)) {
            //	printf("bottom left\n");
            track += 1;
        }
    }

    //brruruhrruh there's such an easier way to do this

    uint32_t neg = -1;

    if (u->toroidal == true) {

        // checks every possible cell
        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {

                if (row == 0 && col == 0) {

                    continue;

                }

                else {

                    uint32_t r_var = (row + r);
                    uint32_t c_var = (col + c);

                    if (r_var == neg) {

                        r_var = u->rows + neg;

                    }

                    else if (r_var >= u->rows) {

                        r_var = r_var % u->rows;
                    }

                    if (c_var == neg) {

                        c_var = u->cols + neg;

                    }

                    else if (c_var >= u->cols) {

                        c_var = c_var % u->cols;
                    }

                    if (uv_get_cell(u, r_var, c_var) == true) {

                        track += 1;
                    }
                }
            }
        }
    }

    return track;
}

void uv_print(Universe *u, FILE *outfile) {
    //print universe to outfile either fputc() or fprintf() to a specified outfile

    //printf("hey\n");

    //char alive = "o";

    //char dead = ".";

    for (uint32_t row = 0; row < u->rows; row++) {

        for (uint32_t col = 0; col < u->cols; col++) {
            //printf("col: %u ", col);

            if (col % u->cols == 0 && row != 0) {
                fprintf(outfile, "%s", "\n");
            }

            if (uv_get_cell(u, row, col) == true) {

                //print "o" into outfile
                fprintf(outfile, "%s", "o");
            }

            else {
                //print "." into outfile
                fprintf(outfile, "%s", ".");
            }
        }
    }

    fprintf(outfile, "%s", "\n");
}
