#include <stdio.h>
#include "../lib/ntru.h"
#include "../lib/debug.h"

int main(void)
{
    struct Crypto myCrypto;
    printf("Size of Crtypo %ld\n", sizeof(myCrypto));
    printf("Size of Poly %ld\n", sizeof(struct Poly));
    printf("Size of Public %ld\n", sizeof(struct Public));
    printf("Size of Private %ld\n", sizeof(struct Private));
    printf("-----------------\n");

    myCrypto = init_Crypto(11, 3, 8);

    print_private(myCrypto.prikey, GET_NAME(myCrypto.prikey));
    print_pubic(myCrypto.pubkey, GET_NAME(myCrypto.pubkey));

    return 0;
}