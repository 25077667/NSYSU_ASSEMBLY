#include <stdio.h>
#include "../lib/e4c_lite.h"
#include "../lib/eea.h"
#include "../lib/poly.h"

#define GET_NAME(var) #var

void print_poly(const struct Poly p, const char *var_name)
{
    printf("This is poly %s: \t", var_name);
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

        struct Poly a_ADD_b = add(a, b);
        print_poly(a_ADD_b, GET_NAME(a_ADD_b));
        struct Poly a_SUB_b = sub(a, b);
        print_poly(a_SUB_b, GET_NAME(a_SUB_b));
        struct Poly a_MUL_b = mul(a, b);
        print_poly(a_MUL_b, GET_NAME(a_MUL_b));
        struct Poly b_DIV_a = div(b, a, 11);
        print_poly(b_DIV_a, GET_NAME(b_DIV_a));
        struct Poly a_DIV_b = div(a, b, 11);
        print_poly(a_DIV_b, GET_NAME(a_DIV_b));

        printf("-----------------------------------\n");
        a = initPolyV(3, 1, 2, 3);
        b = initPolyV(2, 1, 2);
        print_poly(a, GET_NAME(a));
        print_poly(b, GET_NAME(b));
        a_DIV_b = div(a, b, 11);
        print_poly(a_DIV_b, GET_NAME(a_DIV_b));
    }
    E4C_CATCH(RuntimeException)
    {
        printf("Error: %s\n", E4C_EXCEPTION.type->name);
    }

    return 0;
}
