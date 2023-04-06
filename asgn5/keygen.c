#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>
#include "numtheory.h"
#include "randstate.h"
#include "ss.h"
#include <sys/stat.h>

#define OPTIONS "b:i:n:d:s:vh"

int main(int argc, char **argv) {

    uint64_t t = (uint64_t) (time(NULL)); //default time
    uint64_t b = 256; // default
    uint64_t i = 50;
    uint64_t s = t;
    char *pbn = "ss.pub";
    char *pvn = "ss.priv";

    uint64_t *b_ptr = &b;
    uint64_t *i_ptr = &i;
    uint64_t *s_ptr = &s;

    bool case_v = false;
    bool case_h = false;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        case 'b': *b_ptr = strtoll(optarg, NULL, 10); break;

        case 'i': *i_ptr = strtoll(optarg, NULL, 10); break;

        case 'n': pbn = optarg; break;

        case 'd': pvn = optarg; break;

        case 's': *s_ptr = strtoll(optarg, NULL, 10); break;

        case 'v': case_v = true; break;

        case 'h': case_h = true; break;
        }
    }

    //outside of cases

    FILE *pbfile; // default input file
    FILE *pvfile; //default output file

    randstate_init(s);

    mpz_t p, q, n, mpz_d, pq, m;

    mpz_inits(p, q, n, mpz_d, pq, m, NULL);

    ss_make_pub(p, q, n, b, i); //makes public key with b bits and i iterations

    //   gmp_printf("Keygen check: n %Zd\n", n);

    //    printf("ghhgffesfdc   g\n");

    ss_make_priv(mpz_d, pq, p, q); // makes private key

    //   gmp_printf("ss_make_pub(%lu, %lu) =\np: %Zd, q: %Zd\n, n: %Zd\n\n", b, i, p, q, n);

    // gmp_printf("ss_make_priv =\nmpz_d: %Zd, pq: %Zd, p:%Zd\n,q: %Zd\n\n", mpz_d, pq, p, q);

    pbfile = fopen(pbn, "w");

    if (pbfile == NULL) {

        fprintf(stderr, "Incorrect file name. Please use -h for help.\n");
        exit(1);
    }

    char *username = getenv("USER");

    ss_write_pub(n, username, pbfile);

    fclose(pbfile);

    pvfile = fopen(pvn, "w");

    if (pvfile == NULL) {

        fprintf(stderr, "Incorrect file name. Please use -h for help.\n");
        exit(1);
    }

    fchmod(fileno(pvfile), 0600);

    ss_write_priv(pq, mpz_d, pvfile);
    fclose(pvfile);

    if (case_v == true) {

        fprintf(stderr, "user = %s\n", username);
        // prime, p
        gmp_fprintf(stderr, "p  (%d bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        // prime, q
        gmp_fprintf(stderr, "q  (%d bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        // pub key, n
        gmp_fprintf(stderr, "n  (%d bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        // priv mod, pq
        gmp_fprintf(stderr, "pq  (%d bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
        // priv exp, d
        gmp_fprintf(stderr, "d  (%d bits) = %Zd\n", mpz_sizeinbase(mpz_d, 2), mpz_d);
    }

    if (case_h == true) {

        fprintf(stderr, "SYNOPSIS\n   Generates an SS public/private key pair.\n\n");

        fprintf(stderr, "USAGE\n   ./keygen [OPTIONS]\n\n");

        fprintf(stderr, "OPTIONS\n");

        fprintf(stderr, "   -h              Display program help and usage.\n");
        fprintf(stderr, "   -v              Enables verbose program output.\n");
        fprintf(
            stderr, "   -b bits         Minimum bits needed for public key n (default: 256).\n");
        fprintf(stderr,
            "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n");
        fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
        fprintf(stderr, "   -d pvfile       Private key fie (default: ss.priv).\n");
        fprintf(stderr, "   -s seed         Random seed for testing.\n");

        exit(1);
    }

    randstate_clear();

    mpz_clears(p, q, n, mpz_d, pq, m, NULL);
}
