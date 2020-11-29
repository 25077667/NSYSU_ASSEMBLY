#ifndef __NTRU_H__
#define __NTRU_H__

#include "poly.h"

/**
 *
 *                                  ------------
 *           (Hidden) --->          |   NTRU   |      <--- Basic parameter
 *                                  ------------
 *                                    /      \
 *                                   /        \
 *                                  /          \
 *                           -----------    ------------
 *  Caller's privates --->   | Private |    |  Public  |  <--- Public key only
 *                           -----------    ------------
 *                                 \             /
 *                                  \           /
 *                                   \         /
 *                                    ----------
 *                                    | Crypto |      <---  Caller get this
 *                                    ----------
 */



struct Private {
    struct Poly f, f_p;
    int p, q;
};

struct Public {
    struct Poly pubkey;
};

struct Crypto {
    struct Public pubkey;
    struct Private prikey;
};

struct Crypto init_Crypto(int N, int p, int q);

/* FIXME: Needs block encryption */
struct Poly encrypt(struct Poly pubkey, struct Poly r, int p, const char *msg);
/* Return from char *msg */
void decrypt(const struct Poly ciphertext, struct Private prikey, char *msg);

#endif