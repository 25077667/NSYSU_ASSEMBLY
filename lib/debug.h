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
    // TODO: To complete this.
}


#endif