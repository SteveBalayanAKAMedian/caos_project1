#pragma once

#include "divmod.h"
#include <errno.h>
#include <limits.h>

struct divmod_t divmod_init(int b) {
    if (b == 0) {
        errno = 1;
        return (struct divmod_t){0, 0, 0, 0, 0, 0};
    }

    int sign;
    unsigned int d;
    if (b < 0) {
        sign = -1;
        d = -b;
    } else {
        sign = 1;
        d = b;
    }

    int l = 0;
    unsigned int tmp = 1;
    while (tmp < d) {
        ++l;
        tmp <<= 1;
    }

    unsigned long long m = ((1ull << N) * ((1ull << l) - d)) / d + 1;
    int sh1 = l < 1 ? l : 1;
    int sh2;
    if (l - 1 > 0) {
        sh2 = l - 1;
    } else {
        sh2 = 0;
    }

    return (struct divmod_t){l, m, sh1, sh2, sign, d};
}

int div_const(struct divmod_t *divmod, int a) {
    // haven't come up with a better way to fail
    if (divmod->d == 0) {
        errno = MY_DIVISION_BY_ZERO;
        return 0;
    }

    if (a == 0) {
        return 0;
    }

    int sign_n;
    unsigned int n;
    if (a < 0) {
        sign_n = -1;
        n = -a;
    } else {
        sign_n = 1;
        n = a;
    }

    unsigned long long t1 = (divmod->m * n) >> N;
    unsigned int q_abs = (t1 + ((n - t1) >> divmod->sh1)) >> divmod->sh2;
    long long full_ans = sign_n * divmod->sign_d * (int)q_abs;
    if (full_ans >= INT_MIN && full_ans <= INT_MAX) {
        return full_ans;
    } else {
        errno = MY_OVERFLOW;
        return full_ans;
    }
}

int mod_const(struct divmod_t *divmod, int n) {
    if (n == 0) {
        return 0;
    }

    if (divmod->d == 0) {
        errno = MY_DIVISION_BY_ZERO;
        return 0;
    }

    int q = div_const(divmod, n);
    if (errno != 0) {
        return 0;
    }

    long long mod = n - (q * (int)divmod->d * divmod->sign_d);
    if (mod >= INT_MIN && mod <= INT_MAX) {
        return mod;
    } else {
        errno = MY_OVERFLOW;
        return mod;
    }
}