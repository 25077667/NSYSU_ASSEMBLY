#ifndef __EEA_H__
#define __EEA_H__

#include "poly.h"

/*
 * TODO:: Use macros to implement templates of Poly and int
 */

/* s,t are the coefficient of Bézout's lemma*/
struct P_EX_GCD {
    struct Poly s;
    struct Poly t;
    struct Poly gcd;
};

struct I_EX_GCD {  // s,t是貝祖等式中的係數，gcd是a,b的最大公因數s
    int s;
    int t;
    int gcd;
};

struct P_EX_GCD p_extended_euclidean(struct Poly a, struct Poly b);
struct I_EX_GCD i_extended_euclidean(int a, int b);

#endif