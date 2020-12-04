#ifndef __DEBUG_H__
#define __DEBUG_H__
#define GET_NAME(var) #var
#include <stdio.h>

#include "ntru.h"
#include "poly.h"

void print_poly(const struct Poly p, const char *var_name)
{
    printf("This is poly %s: \t", var_name);
    for (int i = p.degree; i >= 0; i--)
        printf("%dX^%d + ", p.coef[i], i);
    printf("\n");
}

void print_private(const struct Private p, const char *var_name)
{
    printf("This is private %s: \n", var_name);

    printf("%s: ", GET_NAME(p.f));
    for (int i = p.f.degree; i >= 0; i--)
        printf("%dX^%d + ", p.f.coef[i], i);

    printf("\n%s: ", GET_NAME(p.f_p));
    for (int i = p.f_p.degree; i >= 0; i--)
        printf("%dX^%d + ", p.f_p.coef[i], i);

    printf("\nN: %d, p: %d, q: %d\n", p.N, p.p, p.q);
}

void print_pubic(const struct Public p, const char *var_name)
{
    printf("This is public %s: \n", var_name);

    printf("%s: ", GET_NAME(p.f));
    for (int i = p.key.degree; i >= 0; i--)
        printf("%dX^%d + ", p.key.coef[i], i);

    printf("\nN: %d, p: %d, q: %d\n", p.N, p.p, p.q);
}

#endif