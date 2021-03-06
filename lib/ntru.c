#include "ntru.h"
#include <stdlib.h>  // srand
#include <time.h>
#include "eea.h"

extern struct Poly ZERO, ONE, NOT_EXIST;

struct NTRU {
    int p, q, N;
    struct Poly f, g;
};

static struct Poly gen_poly(int N, int module)
{
    int argv[N];
    for (int i = 0; i <= N; i++)
        argv[i] = rand() % module;
    return initPolyV2(N, argv);
}

static struct NTRU init_NTRU(int N, int p, int q)
{
    srand(time(NULL));
    struct NTRU target = {
        .N = N,
        .p = p,
        .q = q,
        .f = gen_poly(N - 2, p + 1),
        .g = gen_poly(N - 2, p + 1),
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
        .N = info.N,
        /* h = f_q*g mod q*/
        .key = mul_mod(f_q, info.g, info.q),
    };
}
static struct Private gen_prikey(struct NTRU info)
{
    return (struct Private){
        .p = info.p,
        .q = info.q,
        .f = info.f,
        .N = info.N,
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

static struct Poly char2poly(char c)
{
    int arr[8] = {0};
    char t = 1;
    for (int i = 0; i < 8; i++, t <<= 1)
        if (c & t)
            arr[i] = 1;
    return initPolyV2(8, arr);
}

static char poly2char(const struct Poly m)
{
    char result = 0, t = 1;
    for (int i = 0; i < 8; i++, t <<= 1)
        if (m.coef[i])
            result |= t;
    return result;
}

struct Poly encrypt(char c, struct Public pubkey)
{
    // struct Poly r = gen_poly(pubkey.key.degree, pubkey.q);
    struct Poly r = ONE;
    struct Poly rh = mul_mod(pubkey.key, r, pubkey.q);
    for (int i = 0; i <= rh.degree; i++)
        rh.coef[i] *= pubkey.p;
    struct Poly msg_p = char2poly(c);
    return mod(add(rh, msg_p), pubkey.q);
}

char decrypt(const struct Poly ciphertext, struct Private prikey)
{
    struct Poly a = mul_mod(prikey.f, ciphertext, prikey.q);
    struct Poly m = mul_mod(prikey.f_p, a, prikey.p);
    return poly2char(m);
}
