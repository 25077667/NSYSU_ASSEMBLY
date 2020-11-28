#ifndef __PLOY_H__
#define __POLY_H__
#include <stdbool.h>
#include <stddef.h>
#define LEN 20

struct Poly {
    int coef[LEN];
    size_t size;
};

const struct Poly ZERO = {.coef = {0}, .size = 0};
const struct Poly ONE = {.coef = {1}, .size = 1};

void initPoly(struct Poly *target);
struct Poly initPolyV(int args, ...);
struct Poly add(const struct Poly *a, const struct Poly *b);
struct Poly sub(const struct Poly *a, const struct Poly *b);
struct Poly mul(const struct Poly *a, const struct Poly *b);
struct Poly div(const struct Poly *a, const struct Poly *b);
bool equal(const struct Poly *a, const struct Poly *b);
void copy(struct Poly *dst, const struct Poly *src);

#endif