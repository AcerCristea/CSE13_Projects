#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {

    double e_test = e();
    double me = M_E;
    int eterm = e_terms();

    double pie = pi_euler();
    double mpi = M_PI;
    int pieT = pi_euler_terms();

    double bbp = pi_bbp();
    int bbpT = pi_bbp_terms();

    double mad = pi_madhava();
    int madT = pi_madhava_terms();

    double viete = pi_viete();
    int vieteT = pi_viete_factors();

    double x;
    int opt = 0;
    int sqrtT = sqrt_newton_iters();

    bool case_e = false;
    bool case_b = false;
    bool case_m = false;
    bool case_r = false;
    bool case_v = false;
    bool case_n = false;
    bool case_s = false;
    bool case_h = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            case_e = true;
            case_b = true;
            case_m = true;
            case_r = true;
            case_v = true;
            case_n = true;
            break;

        case 'e': case_e = true; break;
        case 'b': case_b = true; break;
        case 'm': case_m = true; break;
        case 'r': case_r = true; break;
        case 'v': case_v = true; break;
        case 'n': case_n = true; break;
        case 's': case_s = true; break;

        case 'h': case_h = true; break;
        }
    }

    if (case_e == true) {
        printf("e() = %16.15lf, ", e_test);
        printf("M_E = %16.15lf, ", me);
        printf("diff = %16.15lf\n", absolute(e_test - M_E));

        if (case_s == true) {
            printf("e() terms = %d\n", eterm);
        }
    }

    if (case_r == true) {
        printf("pi_euler() = %16.15lf, ", pie);
        printf("M_PI = %16.15lf, ", mpi);
        printf("diff = %16.15f\n", absolute(pie - M_PI));

        if (case_s == true) {
            printf("pi_euler() terms = %d\n", pieT);
        }
    }

    if (case_b == true) {
        printf("pi_bbp() = %16.15lf, ", bbp);
        printf("M_PI = %16.15lf, ", mpi);
        printf("diff = %16.15f\n", absolute(bbp - M_PI));

        if (case_s == true) {
            printf("pi_bbp() terms = %d\n", bbpT);
        }
    }

    if (case_m == true) {
        printf("pi_madhava() = %16.15lf, ", mad);
        printf("M_PI = %16.15lf, ", mpi);
        printf("diff = %16.15f\n", absolute(mad - M_PI));

        if (case_s == true) {
            printf("pi_madhava() terms = %d\n", madT);
        }
    }

    if (case_v == true) {
        printf("pi_viete() = %16.15lf, ", viete);
        printf("M_PI = %16.15lf, ", mpi);
        printf("diff = %16.15f\n", absolute(viete - M_PI));

        if (case_s == true) {
            printf("pi_viete() terms = %d\n", vieteT);
        }
    }

    if (case_n == true) {
        for (x = 0; x < 10; x += 0.1) {
            double sqrt1 = sqrt_newton(x);
            double sqrt2 = sqrt(x);
            printf("sqrt_newton(%8.6lf) = ", x);
            printf("%16.15lf, ", sqrt1);
            printf("sqrt(%8.6lf) = ", x);
            printf("%16.15lf, ", sqrt2);
            printf("diff = %16.15lf\n", absolute(sqrt1 - sqrt2));
            if (case_s == true) {
                printf("sqrt_terms() = %d\n", sqrtT);
            }
        }
    }
    if (case_h == true) {

        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n");
        printf("\n");

        printf("OPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
    }

    if ((case_e == false) && (case_b == false) && (case_m == false) && (case_r == false)
        && (case_v == false) && (case_n == false) && (case_s == true) && (case_h == false)) {

        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n");
        printf("\n");

        printf("OPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
    }

    if ((case_e == false) && (case_b == false) && (case_m == false) && (case_r == false)
        && (case_v == false) && (case_n == false) && (case_s == false) && (case_h == false)) {

        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n");
        printf("\n");

        printf("OPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
    }

    return 0;
}
