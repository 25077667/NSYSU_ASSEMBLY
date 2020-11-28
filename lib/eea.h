#ifndef __EEA_H__
#define __EEA_H__

#include "poly.h"

struct EX_GCD {  // s,t是貝祖等式中的係數，gcd是a,b的最大公因數
    struct Poly s;
    struct Poly t;
    struct Poly gcd;
};

struct EX_GCD extended_euclidean(struct Poly *a, struct Poly *b);

#endif