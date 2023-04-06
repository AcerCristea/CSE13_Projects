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

#define OPTIONS "i:o:vh"

int main(int argc, char **argv) {

    int input_file = STDIN_FILENO; //stdin default

    int output_file = STDOUT_FILENO; // stdout default

    bool case_v = false;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        case 'i': input_file = open(optarg, O_RDONLY); break;

        case 'o': output_file = open(optarg, O_RDWR); break;

        case 'v': case_v = true; break;

        case 'h':

            fprintf(stderr,
                "SYNOPSIS\n   Decompresses files using the LZ78 decompression algorithm.\n "
                "  Used with files compressed with the corresponding decoder.\n\nUSAGE\n   "
                "./decode [-vh] [-i input] [-o output]\n\nOPTIONS\n   -v          Display "
                "compression statistics\n   -i input    Specify input to decompress (stdin "
                "by default)\n   -o output   Specify output of decompressed input (stdout "
                "by default)\n   -h          Display program usage\n");
            exit(1);

            break;
        }
    }

    if (input_file <= 0) {

        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    if (output_file <= 0) {

        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    FileHeader in = { 0 };

    FileHeader *in_p = &in;

    struct stat stats;

    fstat(input_file, &stats);

    fchmod(input_file, stats.st_mode);

    in.magic = MAGIC;
    in.protection = stats.st_mode;

    read_header(input_file, in_p);

    //START OF DECOMPRESSION
    WordTable *table = wt_create();

    uint8_t curr_sym = 0;

    uint16_t curr_code = 0;

    uint16_t next_code = START_CODE;

    while (read_pair(input_file, &curr_code, &curr_sym, log2(next_code) + 1)) {

        //    printf("curr_code = %hu\n", curr_code);
        //    printf("curr_sym = %c\n", curr_sym);

        table[next_code] = word_append_sym(table[curr_code], curr_sym);

        write_word(output_file, table[next_code]);
        next_code = next_code + 1;

        if (next_code == MAX_CODE) {
            wt_reset(table);
            next_code = START_CODE;
        }

    } //end of while loop

    flush_words(output_file);
    wt_delete(table);

    if (case_v == true) {

        double percentage = 100 * (1 - ((double) (total_syms / 8) / (double) total_bits));

        fprintf(stderr, "Compressed file size: %lu bytes\n", total_syms / 8);
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", total_bits);
        fprintf(stderr, "Compression ratio: %.2f%%\n", percentage);
    }

    close(input_file);
    close(output_file);

    return 0;
}
