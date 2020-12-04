#ifndef __EEA_H__
#define __EEA_H__

#include "poly.h"

/*
 * TODO:: Use macros to implement templates of Poly and int
 */

/* s,t are the coefficient of Bézout's lemma*/
struct EX_GCD_P {
    struct Poly s;
    struct Poly t;
    struct Poly gcd;
};

struct EX_GCD_I {
    int s;
    int t;
    int gcd;
};

struct EX_GCD_P extended_euclidean_p(struct Poly a, struct Poly b, int module);
struct EX_GCD_I extended_euclidean_i(int a, int b);

int inverse_i(int a, int module);
struct Poly inverse_p(struct Poly a, struct Poly module, int coprime);

#endif