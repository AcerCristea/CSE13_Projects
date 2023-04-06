#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#include "numtheory.h"
#include "randstate.h"
#include "ss.h"

void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {

    mpz_t double_p, psub, qsub, g, lcm, pq, rem_p, rem_q;

    mpz_inits(double_p, psub, qsub, g, lcm, pq, rem_p, rem_q, NULL);

    do {

        uint64_t low = nbits / 5; //range from nbits/5 to (2*nbits)/5
        uint64_t upp = (2 * nbits) / 5;

        uint64_t pbits, qbits, rand;

        rand = random();
        pbits = rand % (upp - low) + low;

        qbits = nbits - pbits - pbits; // leftover put in q

        make_prime(p, pbits, iters); //first prime number p not working

        make_prime(q, qbits, iters); // second prime number q not working

        mpz_sub_ui(psub, p, 1); // psub = p - 1

        mpz_sub_ui(qsub, q, 1); // qsub = q-1

        mpz_mod(rem_q, q, psub);

        mpz_mod(rem_p, qsub, p);

        mpz_mul(double_p, p, p); // need to double for n = p^2 * q

        mpz_mul(n, double_p, q); // n = p^2 * q

        //  gmp_printf("make_pub public key: %Zd\n", n);

    } while ((mpz_cmp_ui(rem_p, 0) <= 0) || (mpz_cmp_ui(rem_q, 0) <= 0));

    mpz_clears(double_p, psub, qsub, g, lcm, pq, rem_p, rem_q, NULL);
}

void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {

    //gmp_printf("p: %Zd\n", p);
    //gmp_printf("q: %Zd\n", q);

    //Creates a new SS private key d given primes p and q and the public key n. To compute d, simply compute the inverse of n modulo λ(pq) = lcm(p − 1,q − 1).

    // lcm(p-1, q-1) = (p-1 * q-1) / gcd(p-1, q-1)

    mpz_t psub, qsub, g, lcm, mul_pq, n;
    mpz_inits(psub, qsub, g, lcm, mul_pq, n, NULL);

    mpz_sub_ui(psub, p, 1); // p - 1
    mpz_sub_ui(qsub, q, 1); // q - 1

    gcd(g, psub, qsub);
    //  gmp_printf("g: %Zd\n", g);

    mpz_mul(mul_pq, psub, qsub);

    mpz_mul(pq, p, q);

    mpz_mul(n, pq, p);

    //gmp_printf("pq: %Zd\n", pq);
    //gmp_printf("pq: %Zd\n", pq);
    mpz_fdiv_q(lcm, mul_pq, g); // calculating the lcm
    //gmp_printf("lcm: %Zd\n", lcm);

    mod_inverse(d, n, lcm);

    // gmp_printf("d:  %Zd\n", d);

    mpz_clears(psub, qsub, g, lcm, mul_pq, n, NULL);
}

void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {

    // gmp_printf("written public key: %Zd\n", n);

    gmp_fprintf(pbfile, "%Zx\n", n);
    gmp_fprintf(pbfile, "%s\n", username);
}

void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {

    gmp_fprintf(pvfile, "%Zx\n", pq);

    gmp_fprintf(pvfile, "%Zx\n", d);
}

void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {

    gmp_fscanf(pbfile, "%Zx\n", n);
    gmp_fscanf(pbfile, "%s\n", username);
}

void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {

    gmp_fscanf(pvfile, "%Zx\n", pq);
    gmp_fscanf(pvfile, "%Zx\n", d);
}

void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {

    pow_mod(c, m, n, n);
}

void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {

    mpz_t sqrt_n;

    mpz_inits(sqrt_n, NULL);

    mpz_sqrt(sqrt_n, n);

    uint64_t size = mpz_sizeinbase(sqrt_n, 2);

    uint64_t k = (size - 1) / 8;
    //  printf("k: %lu\n", k);

    // dynamically allocate array to hold k bytes --> block
    uint8_t *arr = (uint8_t *) calloc(k + 1, sizeof(uint8_t));
    // while loop variables
    mpz_t m, c; // read bytes & encrypted number
    mpz_inits(m, c, NULL);

    while (!feof(infile)) { // not end of file
        // set zeroth byte to 0xFF
        arr[0] = 0xFF;
        size_t j = fread(arr + 1, sizeof(uint8_t), k - 1, infile);
        //printf("j: %lu\n", j);
        // b) mpz_import() -> convert read bytes into m
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, arr);

        ss_encrypt(c, m, n);

        gmp_fprintf(outfile, "%Zx\n", c);
    }

    mpz_clears(m, c, sqrt_n, NULL);
    free(arr);
}

void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {

    pow_mod(m, c, d, pq);
}

void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t pq, const mpz_t d) {

    uint64_t size = mpz_sizeinbase(pq, 2); // overestimation on sqrt(n)

    uint64_t k = (size - 1) / 8;
    //printf("k: %lu\n", k);

    // dynamically allocate array to hold k bytes --> block
    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t));

    arr[0] = 0xFF;
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    size_t j;

    while (!feof(infile)) {

        gmp_fscanf(infile, "%Zx\n", c); // scan in hex

        ss_decrypt(m, c, d, pq); // decrypt c back into m

        mpz_export(arr, &j, 1, sizeof(uint8_t), 1, 0, m); // convert m into bytes

        //j is a size write now needs to be int for fwrite

        int jsub = (int) j;

        fwrite(arr + 1, sizeof(uint8_t), jsub - 1, outfile);
    }

    free(arr);
    mpz_clears(c, m, NULL);
}
