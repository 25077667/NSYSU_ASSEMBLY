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
    int p, q, N;
};

struct Public {
    struct Poly key;
    int p, q, N;
};

struct Crypto {
    struct Public pubkey;
    struct Private prikey;
};

struct Crypto init_Crypto(int N, int p, int q);

/* Encrypt each char to a Poly */
struct Poly encrypt(char c, struct Public pubkey);
/* Return the char */
char decrypt(const struct Poly ciphertext, struct Private prikey);

#endif
