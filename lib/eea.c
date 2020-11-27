/*
 * Extended euclidean algorithm
 * 2020-11-27
 * SCC, Koul and Max @ NSYSU
 *
 */

#include "eea.h"

struct P_EX_GCD p_extended_euclidean(struct Poly a, struct Poly b)
{
    if (equal(b, ZERO))
        return (struct P_EX_GCD){.s = ONE, .t = ZERO, .gcd = ZERO};

    struct Poly old_r = a, r = b;
    struct Poly old_s = ONE, s = ZERO;
    struct Poly old_t = ZERO, t = ONE;

    while (!equal(r, ZERO)) {
        struct Poly q = div(old_r, r);
        struct Poly temp = old_r;
        old_r = r;
        r = sub(temp, mul(q, r));
        temp = old_s;
        old_s = s;
        s = sub(temp, mul(q, s));
        temp = old_t;
        old_t = t;
        t = sub(temp, mul(q, t));
    }

    return (struct P_EX_GCD){.s = old_s, .t = old_t, .gcd = old_r};
}

struct I_EX_GCD i_extended_euclidean(int a, int b)
{
    if (b == 0)
        return (struct I_EX_GCD){.s = 1, .t = 0, .gcd = 0};

    int old_r = a, r = b;
    int old_s = 1, s = 0;
    int old_t = 0, t = 1;
    while (r != 0) {
        int q = old_r / r;
        int temp = old_r;
        old_r = r;
        r = temp - q * r;
        temp = old_s;
        old_s = s;
        s = temp - q * s;
        temp = old_t;
        old_t = t;
        t = temp - q * t;
    }
    return (struct I_EX_GCD){.s = old_s, .t = old_t, .gcd = old_r};
}