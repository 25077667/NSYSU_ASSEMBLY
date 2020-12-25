#ifndef __POLY_H__
#define __POLY_H__
#include <stdbool.h>
#include <stddef.h>
#define LEN 168

struct Poly {
    unsigned int coef[LEN];
    int degree;
};

void initPoly(struct Poly *target);
/*
 * The first element is the numbers of terms.
 * Eg: 4, 1, 2, 3, 4
 * Is 4 terms, 1 + 2X + 3X^2 + 4X^3
 */
struct Poly initPolyV(int args, ...);
struct Poly initPolyV2(int argc, int *argv);
struct Poly add(struct Poly a, struct Poly b);
struct Poly sub(struct Poly a, struct Poly b);
struct Poly mul_mod(struct Poly a, struct Poly b, int module);
/* Return a/b, gurante divide, and all coefficients are integers in the module*/
/* div name is rather simple, but the memory management can be a bitch. */
struct Poly div2(struct Poly a, struct Poly b, int module);
/* Return the ploy which mod module = 1*/
struct Poly mod(struct Poly a, int module);

bool equal(struct Poly a, struct Poly b);
/* Return `coef` * X^(`degree`) */
struct Poly unitary(int coef, int degree);

#endif