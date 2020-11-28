#ifndef __PLOY_H__
#define __POLY_H__
#include <stdbool.h>
#include <stddef.h>
#define LEN 20

struct Poly {
    unsigned int coef[LEN];
    size_t degree;
};

const struct Poly ZERO = {.coef = {0}, .degree = 0};
const struct Poly ONE = {.coef = {1}, .degree = 0};
const struct Poly NOT_EXIT = {.coef = {0}, .degree = -1};

void initPoly(struct Poly *target);
struct Poly initPolyV(int args, ...);
struct Poly add(struct Poly a, struct Poly b);
struct Poly sub(struct Poly a, struct Poly b);
struct Poly mul(struct Poly a, struct Poly b);
/* Return a/b, gurante divide, and all coefficients are integers in the module*/
struct Poly div(struct Poly a, struct Poly b, int module);
/* Return the ploy which mod module = 1*/
struct Poly mod(struct Poly a, int module);

bool equal(struct Poly a, struct Poly b);
/* Return `coef` * X^(`degree`) */
struct Poly unitary(int coef, int degree);

#endif