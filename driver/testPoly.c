#include <stdio.h>
#include "../lib/e4c_lite.h"
#include "../lib/eea.h"
#include "../lib/poly.h"

#define GET_NAME(var) #var

void print_poly(const struct Poly p, const char *var_name)
{
    printf("This is poly %s: ", var_name);
    for (int i = p.degree; i >= 0; i--)
        printf("%dX^%d + ", p.coef[i], i);
    printf("\n");
}


extern struct Poly ZERO;
extern struct Poly ONE;
extern struct Poly NOT_EXIST;

int main(void)
{
    E4C_TRY
    {
        print_poly(ZERO, GET_NAME(ZERO));
        print_poly(ONE, GET_NAME(ONE));
        print_poly(NOT_EXIST, GET_NAME(NOT_EXIST));

        struct Poly a = {.coef = {1, 2, 3, 4, 5}, .degree = 4},
                    b = {.coef = {1, 2, 3, 4, 5, 6, 7, 8, 9}, .degree = 8};
        print_poly(a, GET_NAME(a));
        print_poly(b, GET_NAME(b));

        struct Poly c = add(a, b);
        print_poly(c, GET_NAME(c));
        struct Poly d = sub(a, b);
        print_poly(d, GET_NAME(d));
        struct Poly e = mul(a, b);
        print_poly(e, GET_NAME(e));
        struct Poly f = div(b, a, 0x7fffffff);
        print_poly(f, GET_NAME(f));
    }
    E4C_CATCH(RuntimeException)
    {
        printf("Error: %s\n", E4C_EXCEPTION.type->name);
    }

    return 0;
}