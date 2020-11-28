/*
 * Extended euclidean algorithm
 * 2020-11-27
 * SCC, Koul and Max @ NSYSU
 *
 */

#include "eea.h"

struct EX_GCD extended_euclidean(struct Poly *a, struct Poly *b)
{
    struct EX_GCD ex_gcd;

    if (equal(b, &ZERO)) {  // b=0時直接結束求解
        ex_gcd.s = ONE;
        ex_gcd.t = ZERO;
        ex_gcd.gcd = ZERO;
        return ex_gcd;
    }

    struct Poly old_r, old_s, old_t, r, s, t;

    copy(&old_r, a);
    copy(&r, b);

    copy(&old_s, &ONE);
    copy(&s, &ZERO);

    copy(&old_t, &ZERO);
    copy(&t, &ONE);

    while (!equal(&r, &ZERO)) {  //按擴展歐基里德算法進行循環
        struct Poly q = div(&old_r, &r);
        struct Poly temp = old_r;
        // FIXME
        old_r = r;
        r = temp - q * r;
        temp = old_s;
        old_s = s;
        s = temp - q * s;
        temp = old_t;
        old_t = t;
        t = temp - q * t;
    }
    ex_gcd.s = old_s;
    ex_gcd.t = old_t;
    ex_gcd.gcd = old_r;
    return ex_gcd;
}