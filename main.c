#include "divmod.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int TEST_CASE_1() {
    int passed = 1;
    for (int d = 1; d != 100; ++d) {
        for (int n = 1; n != 100; ++n) {
            if (d == 0) {
                continue;
            }

            int real_q = n / d;
            int real_mod = n % d;
            struct divmod_t dm = divmod_init(d);
            int q = div_const(&dm, n);

            if (errno != 0) {
                printf("n = %d, d = %d, n / d = %d, my ans = %d; errno = %d\n",
                       n, d, real_q, q, errno);
                passed = 0;
                errno = 0;
            } else if (real_q != q) {
                printf("n = %d, d = %d, n / d = %d, my ans = %d\n", n, d,
                       real_q, q);
                passed = 0;
            }

            int r = mod_const(&dm, n);
            if (errno != 0) {
                printf(
                    "n = %d, d = %d, n mod d = %d, my ans = %d; errno = %d\n",
                    n, d, real_mod, r, errno);
                passed = 0;
                errno = 0;
            } else if (real_mod != r) {
                printf("n = %d, d = %d, n mod d = %d, my ans = %d\n", n, d,
                       real_mod, r);
                passed = 0;
            }
        }
    }
    errno = 0;
    return passed;
}

int TEST_CASE_2() {
    int passed = 1;
    for (int d = -100; d != 100; ++d) {
        for (int n = -100; n != 100; ++n) {
            if (d == 0) {
                continue;
            }

            int real_q = n / d;
            int real_mod = n % d;
            struct divmod_t dm = divmod_init(d);
            int q = div_const(&dm, n);

            if (errno != 0) {
                printf("n = %d, d = %d, n / d = %d, my ans = %d; errno = %d\n",
                       n, d, real_q, q, errno);
                passed = 0;
                errno = 0;
            } else if (real_q != q) {
                printf("n = %d, d = %d, n / d = %d, my ans = %d\n", n, d,
                       real_q, q);
                passed = 0;
            }

            int r = mod_const(&dm, n);
            if (errno != 0) {
                printf(
                    "n = %d, d = %d, n mod d = %d, my ans = %d; errno = %d\n",
                    n, d, real_mod, r, errno);
                passed = 0;
                errno = 0;
            } else if (real_mod != r) {
                printf("n = %d, d = %d, n mod d = %d, my ans = %d\n", n, d,
                       real_mod, r);
                passed = 0;
            }
        }
    }
    errno = 0;
    return passed;
}

int edge_case_div(int n, int d) {
    int passed = 1;

    struct divmod_t dm = divmod_init(d);
    long long real_q = n / d;
    int q = div_const(&dm, n);
    if (INT_MIN <= real_q && real_q <= INT_MAX) {

        if (errno != 0 || q != real_q) {
            printf("n = %d, d = %d, n / d = %lld, my ans = %d; errno = %d\n", n,
                   d, real_q, q, errno);
            passed = 0;
            errno = 0;
        }
    } else {
        if (errno == 0) {
            printf("n = %d, d = %d, n / d = %lld, my ans = %d; errno = %d\n", n,
                   d, real_q, q, errno);
            passed = 0;
            errno = 0;
        }
    }
    return passed;
}

int edge_case_mod(int n, int d) {
    int passed = 1;

    struct divmod_t dm = divmod_init(d);
    long long real_mod = n % d;
    long long real_q = n / d;
    int r = mod_const(&dm, n);
    if (INT_MIN <= real_q && real_q <= INT_MAX) {
        if (INT_MIN <= real_mod && real_mod <= INT_MAX) {
            if (errno != 0 || r != real_mod) {
                passed = 0;
                errno = 0;
                printf(
                    "n = %d, d = %d, n mod d = %lld, my ans = %d; errno = %d\n",
                    n, d, real_mod, r, errno);
            }
        } else {
            if (errno == 0) {
                passed = 0;
                printf(
                    "n = %d, d = %d, n mod d = %lld, my ans = %d; errno = %d\n",
                    n, d, real_mod, r, errno);
            }
        }
    } else {
        if (errno == 0) {
            printf("n = %d, d = %d, n / d = %lld, my ans = %d; errno = %d\n", n,
                   d, real_q, r, errno);
            passed = 0;
            errno = 0;
        }
    }
    return passed;
}

// edge cases
int TEST_CASE_3() {
    int number_of_subtests = 8;
    int passed = 0;

    int d = INT_MIN;

    int n = INT_MAX;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    n = INT_MIN;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    n = 1;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    n = -1;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    errno = 0;
    return passed == number_of_subtests;
}

int TEST_CASE_4() {
    int number_of_subtests = 8;
    int passed = 0;

    int d = INT_MAX;

    int n = INT_MAX;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    n = INT_MIN;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    n = 1;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    n = -1;
    passed += edge_case_div(n, d);
    passed += edge_case_mod(n, d);

    errno = 0;
    return passed == number_of_subtests;
}

int random_integer() {
    long long lower_bound = INT_MIN;
    long long upper_bound = INT_MAX;

    srand(1337);

    long long range = upper_bound - lower_bound + 1;
    long long random_number = rand() % range + lower_bound;

    return (int)random_number;
}

// random
int TEST_CASE_5() {
    int passed = 1;
    for (int i = 0; i != 1000000; ++i) {
        int n = random_integer();
        int d = random_integer();

        if (d == 0) {
            continue;
        }

        int real_q = n / d;
        int real_mod = n % d;
        struct divmod_t dm = divmod_init(d);
        int q = div_const(&dm, n);

        if (errno != 0) {
            printf("n = %d, d = %d, n / d = %d, my ans = %d; errno = %d\n", n,
                   d, real_q, q, errno);
            passed = 0;
            errno = 0;
        } else if (real_q != q) {
            printf("n = %d, d = %d, n / d = %d, my ans = %d\n", n, d, real_q,
                   q);
            passed = 0;
        }

        int r = mod_const(&dm, n);
        if (errno != 0) {
            printf("n = %d, d = %d, n mod d = %d, my ans = %d; errno = %d\n", n,
                   d, real_mod, r, errno);
            passed = 0;
            errno = 0;
        } else if (real_mod != r) {
            printf("n = %d, d = %d, n mod d = %d, my ans = %d\n", n, d,
                   real_mod, r);
            passed = 0;
        }
    }
    errno = 0;
    return passed;
}

int main() {
    int t1 = TEST_CASE_1();
    if (t1) {
        printf("test 1 passed\n");
    } else {
        printf("test 1 failed\n");
    }

    int t2 = TEST_CASE_2();
    if (t2) {
        printf("test 2 passed\n");
    } else {
        printf("test 2 failed\n");
    }

    int t3 = TEST_CASE_3();
    if (t3) {
        printf("test 3 passed\n");
    } else {
        printf("test 3 failed\n");
    }

    int t4 = TEST_CASE_4();
    if (t4) {
        printf("test 4 passed\n");
    } else {
        printf("test 4 failed\n");
    }

    int t5 = TEST_CASE_5();
    if (t5) {
        printf("test 5 passed\n");
    } else {
        printf("test 5 failed\n");
    }
    return 0;
}