/*
 * Extended euclidean algorithm
 * 2020-11-27
 * SCC, Koul and Max @ NSYSU
 *
 */

#include "eea.h"

extern struct Poly ZERO;
extern struct Poly ONE;
extern struct Poly NOT_EXIST;

struct EX_GCD_P extended_euclidean_p(struct Poly a, struct Poly b, int module)
{
    if (equal(b, ZERO))
        return (struct EX_GCD_P){.s = ONE, .t = ZERO, .gcd = ZERO};

    struct Poly old_r = a, r = b;
    struct Poly old_s = ONE, s = ZERO;
    struct Poly old_t = ZERO, t = ONE;

    while (!equal(r, ZERO)) {
        struct Poly q = div(old_r, r, module);
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

    return (struct EX_GCD_P){.s = old_s, .t = old_t, .gcd = old_r};
}

struct EX_GCD_I extended_euclidean_i(int a, int b)
{
    if (b == 0)
        return (struct EX_GCD_I){.s = 1, .t = 0, .gcd = a};

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
    return (struct EX_GCD_I){.s = old_s, .t = old_t, .gcd = old_r};
}

int inverse_i(int a, int module)
{
    struct EX_GCD_I eea = extended_euclidean_i(a, module);
    return ((eea.gcd == 1) ? (eea.s + module) % module : -1);
}

struct Poly inverse_p(struct Poly a, struct Poly module, int coprime)
{
    struct EX_GCD_P eea = extended_euclidean_p(a, module, coprime);
    return (equal(eea.gcd, ONE) ? mod(add(eea.s, module), coprime) : NOT_EXIST);
}
