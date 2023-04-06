#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "word.h"
#include "trie.h"
#include "code.h"
#include "io.h"
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <check.h>

int main(void) {

    int infile = open("infile.txt", O_RDONLY);

    uint8_t curr_sym = 0;
    //uint8_t prev_sym = 0;

    while (read_sym(infile, &curr_sym) == true) {

        printf("%c", curr_sym);
    }

    return 0;
}
