#include "ntru.h"
#include "eea.h"

extern struct Poly ZERO, ONE, NOT_EXIST;

struct NTRU {
    int p, q, N;
    struct Poly f, g, r;
};

static struct Poly gen_poly(int N, int module)
{
    // FIXME: Init as some random methods
    return initPolyV(1, 2, 3);
}

static struct NTRU init_NTRU(int N, int p, int q)
{
    struct NTRU target = {
        .N = N,
        .p = p,
        .q = q,
        .f = gen_poly(N, 0x7fffffff),
        .g = gen_poly(N, 0x7fffffff),
        .r = gen_poly(N, 0x7fffffff),
    };
    return target;
}

static struct Poly gen_pubkey(struct NTRU info) {}
static struct Private gen_prikey(struct NTRU info) {}
struct Crypto init_Crypto(int N, int p, int q)
{
    struct NTRU myNTRU = init_NTRU(N, p, q);
    struct Crypto target = {.pubkey = gen_pubkey(myNTRU),
                            .prikey = gen_prikey(myNTRU)};
    return target;
}

static struct Poly msg2poly(const char *msg) {}
static void poly2msg(const struct Poly m, char *msg) {}

struct Poly encrypt(struct Poly pubkey, struct Poly r, int p, const char *msg)
{
    struct Poly rh = mul(pubkey, r);
    for (int i = 0; i <= rh.degree; i++)
        rh.coef[i] *= p;
    struct Poly msg_p = msg2poly(msg);
    return add(rh, msg_p);
}

void decrypt(const struct Poly ciphertext, struct Private prikey, char *msg)
{
    struct Poly a = mod(mul(prikey.f, ciphertext), prikey.q);
    struct Poly m = mod(mul(prikey.f_p, a), prikey.p);
    poly2msg(m, msg);
}