#include "poly.h"
#include <stdarg.h>
#include <string.h>
#include "e4c_lite.h"

#define MAX(a, b)               \
    ({                          \
        __typeof__(a) _a = (a); \
        __typeof__(b) _b = (b); \
        _a > _b ? _a : _b;      \
    })

extern int inverse_i(int a, int module);

const struct Poly ZERO = {.coef = {0}, .degree = 0};
const struct Poly ONE = {.coef = {1}, .degree = 0};
const struct Poly NOT_EXIST = {.coef = {0}, .degree = -1};

static inline void fix_deg(struct Poly *target)
{
    for (int i = LEN - 1; i >= 0; i--)
        if (target->coef[i]) {
            target->degree = i;
            break;
        }
}

// init as zero
void initPoly(struct Poly *target)
{
    memset(target, 0, sizeof(struct Poly));
}

struct Poly initPolyV(int args, ...)
{
    struct Poly target = {.coef = {0}, .degree = 0};
    va_list ap;
    va_start(ap, args);

    target.degree = args - 1;
    for (int i = 0; i < args; i++)
        target.coef[i] = va_arg(ap, int);

    va_end(ap);
    return target;
}

struct Poly add(struct Poly a, struct Poly b)
{
    int len = MAX(a.degree, b.degree);
    struct Poly target = {.coef = {0}, .degree = len};
    for (int i = 0; i <= len; i++)
        target.coef[i] = a.coef[i] + b.coef[i];
    fix_deg(&target);
    return target;
}

struct Poly sub(struct Poly a, struct Poly b)
{
    int len = MAX(a.degree, b.degree);
    struct Poly target = {.coef = {0}, .degree = len};
    for (int i = 0; i <= len; i++)
        target.coef[i] = a.coef[i] - b.coef[i];
    fix_deg(&target);
    return target;
}

struct Poly mul(struct Poly a, struct Poly b)
{
    struct Poly target = {.coef = {0}, .degree = a.degree + b.degree};
    for (int i = 0; i <= a.degree; i++)
        for (int j = 0; j <= b.degree; j++)
            target.coef[i + j] += a.coef[i] * b.coef[j];

    fix_deg(&target);
    return target;
}

struct Poly div(struct Poly a, struct Poly b, int module)
{
    struct Poly quotient = {.coef = {0}, .degree = 0};
    int index = MAX(a.degree, b.degree);
    if (a.degree >= b.degree) {
        /* a's degree is greather or equal b's degree */
        int inverse = inverse_i(b.coef[b.degree], module);
        if (inverse == -1)
            E4C_THROW(RuntimeException, "Inverse not found");
        for (int i = index; i >= b.degree; i--) {
            unsigned int coef = (a.coef[i] * inverse) % module;
            /* Simulate long division: a -= b * quotient[i] */
            a = mod(sub(a, mod(mul(b, unitary(coef, i - b.degree)), module)),
                    module);
            quotient = mod(add(quotient, unitary(coef, i - b.degree)), module);
        }
        fix_deg(&quotient);
    }
    return quotient;
}

struct Poly mod(struct Poly a, int module)
{
    for (int i = a.degree; i >= 0; i--)
        a.coef[i] = (a.coef[i] + module) % module;
    return a;
}

bool equal(struct Poly a, struct Poly b)
{
    if (a.degree != b.degree)
        return false;
    else {
        for (int i = 0; i <= b.degree; i++)
            if (a.coef[i] - b.coef[i])
                return false;
        return true;
    }
}

struct Poly unitary(int coef, int degree)
{
    struct Poly result;
    initPoly(&result);
    result.coef[degree] = coef;
    result.degree = degree;
    return result;
}
