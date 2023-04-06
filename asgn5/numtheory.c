#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include "numtheory.h"
#include "randstate.h"
#include <stdlib.h>

void gcd(mpz_t g, const mpz_t a, const mpz_t b) {

    mpz_t t, x, y;

    mpz_init_set(x, a);
    mpz_init_set(y, b);

    while (mpz_cmp_ui(y, 0) != 0) { //while b != 0

        mpz_init_set(t, y); // t <- b

        mpz_mod(y, x, y); // b = a % b

        mpz_init_set(x, t); // a <- t
    }

    mpz_init_set(g, x); //return a

    mpz_clears(x, y, t, NULL);
}

void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n) {

    mpz_t r, r_p, t, t_p;

    mpz_init_set(r, n); // r <- n
    //6
    mpz_init_set(r_p, a); // r' <- a
        //3

    mpz_init_set_ui(t, 0); // t <- 0

    mpz_init_set_ui(t_p, 1); // t' <- 1

    while (mpz_cmp_ui(r_p, 0) != 0) { // while r_p != 0

        //         gmp_printf("r value:  %Zd\n",r);

        //   gmp_printf("r prime value: %Zd\n",r_p);

        // gmp_printf("t value:  %Zd\n",t);

        //gmp_printf("t prime value: %Zd\n",t_p);

        mpz_t r_mul, r_sub, t_mul, t_sub, q;

        mpz_inits(r_mul, r_sub, t_mul, t_sub, q, NULL);

        mpz_fdiv_q(q, r, r_p); // q = r/r'

        mpz_mul(r_mul, q, r_p); // temp_mul = q * r'

        mpz_sub(r_sub, r, r_mul); // temp_sub = r - temp_mul

        mpz_init_set(r, r_p); // r <- r_p
        mpz_init_set(r_p, r_sub);

        //     gmp_printf("r value:  %Zd\n",r);

        //   gmp_printf("r prime value: %Zd\n",r_p);

        mpz_mul(t_mul, q, t_p); // temp_mul = q * t'
        mpz_sub(t_sub, t, t_mul); // temp_sub = r - temp_mul

        mpz_init_set(t, t_p); // t <- t'
        mpz_init_set(t_p, t_sub);

        //              gmp_printf("t value:  %Zd\n",t);

        //      gmp_printf("t prime value: %Zd\n",t_p);

        //    gmp_printf("\n");

        mpz_clears(q, r_mul, t_mul, r_sub, t_sub, NULL);
    }

    if (mpz_cmp_ui(r, 1) > 0) { // if r > 1

        mpz_init_set_ui(o, 0);

        //     gmp_printf("SHOULD STOP");
        return;

        //should exit // correctly sets o 0 returning no inverse
    }

    if (mpz_cmp_ui(t, 0) < 0) { // if t < 0

        mpz_add(t, t, n);
    }

    mpz_init_set(o, t); // return t
    mpz_clears(r, t, r_p, t_p, NULL);
}

void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n) {

    mpz_t v, p, temp_p, temp_v, temp_d;

    mpz_init_set_ui(v, 1); // v <- 1

    mpz_init_set(p, a); //p <- a

    mpz_init_set(temp_d, d);

    mpz_inits(temp_p, temp_v, NULL);

    while (mpz_cmp_ui(temp_d, 0) > 0) { //while d > 0

        if (mpz_odd_p(temp_d) == 1) { //if d is an odd number

            mpz_mul(temp_v, v, p); // temp_v = v * p

            mpz_mod(v, temp_v, n); // v = temp_v % n
        }

        mpz_mul(temp_p, p, p); // temp_p = p * p

        mpz_mod(p, temp_p, n); // p = temp_p % n

        mpz_fdiv_q_ui(temp_d, temp_d, 2); // d = d/2
    }

    mpz_init_set(o, v); // return v into o
    mpz_clears(v, p, temp_d, temp_v, temp_p, NULL);
}

//n - 1 = 2^s *r

void find_totient(
    mpz_t s, mpz_t r, const mpz_t n) { //TA gave idea for using the totient from a previous quarter
    mpz_t temp_n;
    mpz_t temp_mod;
    mpz_inits(temp_mod, temp_n, NULL);

    mpz_init_set(temp_n, n);

    mpz_sub_ui(temp_n, temp_n, 1);

    mpz_mod_ui(temp_mod, temp_n, 2);

    while (mpz_cmp_ui(temp_mod, 0) == 0) {

        mpz_add_ui(s, s, 1); //s++
        mpz_fdiv_q_ui(temp_n, temp_n, 2);
        mpz_mod_ui(temp_mod, temp_n, 2);
    }

    mpz_init_set(r, temp_n); // r <- n

    mpz_clears(temp_n, temp_mod, NULL);
}

bool is_prime(const mpz_t n, uint64_t iters) {

    if (mpz_cmp_ui(n, 1) <= 0) { // if prime is 0 or negative number, not a prime
        return false;
    }

    mpz_t temp_n, j, y, s, r, nsub, ssub, a, mod;

    mpz_inits(j, y, s, r, nsub, ssub, a, NULL);

    mpz_init_set(temp_n, n);

    //  gmp_printf("temp_n : %Zd\n", temp_n); - giant number makes sense for mpz_t

    find_totient(s, r, n); // sets s and r of const n

    mpz_sub_ui(nsub, temp_n, 1); // n-1 used for cmp later

    mpz_sub_ui(ssub, s, 1); // s-1 used for cmp later

    mpz_init_set_ui(mod, 2);

    //   gmp_printf("nsub: %Zd\nssub: %Zd\n", nsub, ssub);

    uint64_t i;

    for (i = 1; i < iters; i++) {

        //need randtstate for this
        mpz_urandomm(a, state, nsub); // this goes from a to n-2, -2 cuz we do -1 -1

        //   gmp_printf("a: %Zd\n", a);

        if (mpz_cmp_ui(a, 2)
            >= 0) { // only want it starting from 2 - can't do i cuz it starts at a random point

            pow_mod(y, a, r, temp_n); // puts power mod into y

            //   gmp_printf(" beforeeeeeee pow y: %Zd\n", y);

            if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, nsub) != 0)) {

                mpz_init_set_ui(j, 1);

                while ((mpz_cmp(j, ssub) <= 0) && (mpz_cmp(y, nsub) != 0)) {

                    pow_mod(y, y, mod, temp_n);

                    //    gmp_printf("aaaaaaaaftreeeerrrr pow y: %Zd\n", y);

                    if (mpz_cmp_ui(y, 1) == 0) {

                        mpz_clears(temp_n, a, y, mod, r, s, ssub, nsub, NULL);

                        //   gmp_printf("It's 1111111111111\n");

                        return false;
                    }

                    mpz_add_ui(j, j, 1);
                }

                if (mpz_cmp(y, nsub) != 0) {

                    mpz_clears(temp_n, a, y, mod, r, s, ssub, nsub, NULL);
                    return false;
                }
            }

        }

        else {

            continue;
        }
    }

    mpz_clears(temp_n, a, y, mod, r, s, ssub, nsub, NULL);
    return true;
}

void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {

    mpz_t mask;
    mpz_init_set_ui(mask, 2);
    mpz_pow_ui(mask, mask, bits);
    mpz_add_ui(mask, mask, 2);
    //gmp_printf("mask: %Zd\n", mask);

    mpz_urandomb(p, state, bits); // initializes p to be a random integer
    //   gmp_printf("p: %Zd\n", p);

    //  printf("hello\n");

    bool x = is_prime(p, iters);
    //printf("x: %d\n", x);

    while (x == 0) { // while p is not prime
        //printf("inside while loop\n");
        mpz_urandomb(p, state, bits); // find a random p
        //printf("worls\n");
        //random p?
        mpz_xor(p, p, mask);
        //gmp_printf("p2: %Zd\n", p);
        x = is_prime(p, iters);
        //printf("x2: %d\n", x);

        if (x == 1) {
            //        printf("new prime found\n");
            break;
        }
    }
    mpz_clears(mask, NULL);
}
