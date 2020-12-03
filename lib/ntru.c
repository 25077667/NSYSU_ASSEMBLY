#include "ntru.h"
#include "eea.h"

extern struct Poly ZERO, ONE, NOT_EXIST;

struct NTRU {
    int p, q, N;
    struct Poly f, g;
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
    };
    return target;
}

static struct Public gen_pubkey(struct NTRU info)
{
    struct Poly f_q =
        inverse_p(info.f, sub(unitary(1, info.N), unitary(1, 0)), info.q);
    return (struct Public){
        .q = info.q,
        .p = info.p,
        /* h = f_q*g mod q*/
        .h = mod(mul(f_q, info.g), info.q),
    };
}
static struct Private gen_prikey(struct NTRU info)
{
    return (struct Private){
        .p = info.p,
        .q = info.q,
        .f = info.f,
        .f_p =
            inverse_p(info.f, sub(unitary(1, info.N), unitary(1, 0)), info.p),
    };
}

struct Crypto init_Crypto(int N, int p, int q)
{
    struct NTRU myNTRU = init_NTRU(N, p, q);
    struct Crypto target = {.pubkey = gen_pubkey(myNTRU),
                            .prikey = gen_prikey(myNTRU)};
    return target;
}

static struct Poly char2poly(int max_degree, int q, char c) {
    
}

static char poly2char(const struct Poly m, int p, int q) {}

struct Poly encrypt(struct Public pubkey, char c)
{
    // FIXME: Is r mod q? Is r degree is pubkey's degree?
    struct Poly r = gen_poly(pubkey.h.degree, pubkey.q);
    struct Poly rh = mod(mul(pubkey.h, r), pubkey.q);
    for (int i = 0; i <= rh.degree; i++)
        rh.coef[i] *= pubkey.p;
    // FIXME: What is the max_degree of msg_p? (Is N public?)
    struct Poly msg_p = char2poly(pubkey.h.degree, pubkey.q, c);
    return mod(add(rh, msg_p), pubkey.q);
}

char decrypt(const struct Poly ciphertext, struct Private prikey)
{
    struct Poly a = mod(mul(prikey.f, ciphertext), prikey.q);
    struct Poly m = mod(mul(prikey.f_p, a), prikey.p);
    return poly2char(m);
}