#include <stdbool.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include "numtheory.h"
#include "randstate.h"
#include "ss.h"

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {

    char *i_name = NULL;
    char *o_name = NULL;
    char *n_name = "ss.pub";

    bool case_v = false;
    bool case_h = false;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        case 'i': i_name = optarg; break;

        case 'o': o_name = optarg; break;

        case 'n': n_name = optarg; break;

        case 'v': case_v = true; break;
        case 'h': case_h = true; break;
        }
    }

    //outside

    mpz_t n;

    mpz_inits(n, NULL);

    char *username = getenv("USER");

    FILE *input_file = stdin;
    FILE *output_file = stdout;
    FILE *public_key;

    if (i_name != NULL) {

        input_file = fopen(i_name, "r");
    }

    if (input_file == NULL) {

        fprintf(stderr, "Incorrect file name. Please use -h for help.\n");
        exit(1);
    }

    if (o_name != NULL) {

        output_file = fopen(o_name, "w");
    }

    if (output_file == NULL) {

        fprintf(stderr, "Incorrect file name. Please use -h for help.\n");
        exit(1);
    }

    public_key = fopen(n_name, "r");

    if (public_key == NULL) {

        fprintf(stderr, "Incorrect file name. Please use -h for help.\n");
        exit(1);
    }

    ss_read_pub(n, username, public_key);

    fclose(public_key);

    if (case_v == true) {

        fprintf(stderr, "user = %s\n", username);
        gmp_fprintf(stderr, "n (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
    }

    if (case_h == true) {

        fprintf(stderr, "SYNOPSIS\n");
        fprintf(stderr, "   Encrypts data using SS encryption.\nEncrypted data is decrypted by the "
                        "decrypt program.\n\n");
        fprintf(stderr, "USAGE\n");
        fprintf(stderr, "   ./encrypt [OPTIONS]\n\n");
        fprintf(stderr, "OPTIONS\n");
        fprintf(stderr, "   -h              Display program help and usage\n");
        fprintf(stderr, "   -v              Display verbose program output.\n");
        fprintf(stderr, "   -i infile       Input file of data to encrypt (default: stdin).\n");
        fprintf(stderr, "   -o outfile      Output file for encrypted data (default: stdout).\n");
        fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");

        exit(1);
    }

    ss_encrypt_file(input_file, output_file, n);

    fclose(input_file);
    fclose(output_file);

    mpz_clears(n, NULL);
}
