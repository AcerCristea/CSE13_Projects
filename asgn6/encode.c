#include <stdio.h>
#include <inttypes.h>
#include "trie.h"
#include "code.h"
#include "io.h"
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
    bool case_h = false;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        case 'i': input_file = open(optarg, O_RDONLY); break;

        case 'o': output_file = open(optarg, O_RDWR); break;

        case 'v': case_v = true; break;

        case 'h': case_h = true; break;
        }
    }

    if (case_h == true) {
        fprintf(stderr,
            "SYNOPSIS\n   Compresses files using the LZ78 compression algorithm.\n   "
            "Compressed files are decompressed with the corresponding decoder.\n\nUSAGE\n  "
            " ./encode [-vh] [-i input] [-o output]\n\nOPTIONS\n   -v          Display "
            "compression statistics\n   -i input    Specify input to compress (stdin by "
            "default)\n   -o output   Specify output of compressed input (stdout by "
            "default)\n   -h          Display program help and usage\n");
        exit(1);
    }

    if (input_file <= 0) {

        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    if (output_file <= 0) {

        fprintf(stderr, "Error opening file\n");
        exit(1);
    }

    FileHeader out = { 0 };

    FileHeader *out_p = &out;

    struct stat stats;

    fstat(output_file, &stats);

    fchmod(output_file, stats.st_mode);

    out.magic = MAGIC;
    out.protection = stats.st_mode;

    write_header(output_file, out_p);

    //START OF COMPRESSION
    TrieNode *root = trie_create();

    TrieNode *curr_node = root;

    TrieNode *prev_node = NULL;

    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;

    uint16_t next_code = START_CODE;

    while (read_sym(input_file, &curr_sym)) {

        //printf("curr_sym = %c\n", curr_sym);

        TrieNode *next_node = trie_step(curr_node, curr_sym);

        if (next_node != NULL) { //For repeats in the symbols
            prev_node = curr_node;
            curr_node = next_node;
        }

        else {

            write_pair(output_file, curr_node->code, curr_sym, log2(next_code) + 1); //bitlength
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code = next_code + 1;
        }

        if (next_code == MAX_CODE) { //will almost never reach this
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }

        prev_sym = curr_sym;

    } //end of while loop

    if (curr_node != root) { //Rarely enter

        write_pair(output_file, prev_node->code, prev_sym, log2(next_code) + 1);

        next_code = (next_code + 1) % MAX_CODE;
    }

    write_pair(output_file, STOP_CODE, 0, log2(next_code) + 1);
    flush_pairs(output_file);

    trie_delete(root);

    if (case_v == true) {

        double percentage = 100 * (1 - ((double) total_bits / (double) total_syms));

        fprintf(stderr, "Compressed file size: %lu bytes\n", total_bits);
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", total_syms);
        fprintf(stderr, "Compression ratio: %.2f%%\n", percentage);
    }

    close(input_file);
    close(output_file);

    return 0;
}
