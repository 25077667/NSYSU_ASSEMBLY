#include <stdio.h>
#include "../lib/ntru.h"
#include "../lib/debug.h"
#include "../lib/poly.h"
#include "../lib/e4c_lite.h"
#include "../lib/eea.h"


struct Poly char2poly(char c)
{
    int arr[8] = {0};
    char t = 1;
    for (int i = 0; i < 8; i++, t <<= 1)
        if (c & t)
            arr[i] = 1;
    return initPolyV2(8, arr);
}


int main(void)
{
    struct Crypto myCrypto;
    char str[] = "Hello,world";
    char tmp;
    struct Poly cipher;
    printf("Size of Crtypo %ld\n", sizeof(myCrypto));
    printf("Size of Poly %ld\n", sizeof(struct Poly));
    printf("Size of Public %ld\n", sizeof(struct Public));
    printf("Size of Private %ld\n", sizeof(struct Private));
    printf("-----------------\n");

    //myCrypto = init_Crypto(11, 3, 8);
    myCrypto.prikey.f = initPolyV(11,1,1,1,0,1,0,10,0,10,0,10);
    myCrypto.prikey.f_p = initPolyV(10,0,1,2,2,2,1,0,1,0,1);
    myCrypto.prikey.N = 11;
    myCrypto.prikey.p = 3;
    myCrypto.prikey.q = 61;
    myCrypto.pubkey.key = initPolyV(11,50,5,32,36,31,53,28,46,25,49,11);
    myCrypto.pubkey.N = 11;
    myCrypto.pubkey.p = 3;
    myCrypto.pubkey.q = 61;
    print_private(myCrypto.prikey, GET_NAME(myCrypto.prikey));
    print_pubic(myCrypto.pubkey, GET_NAME(myCrypto.pubkey));
    printf("-----------------\n");
  
    E4C_TRY{

          cipher = encrypt(str[0],myCrypto.pubkey);
          /*struct Poly r = initPolyV(10,1,0,10,1,0,0,1,0,10);
          struct Poly rh = mod(mul(myCrypto.pubkey.key, r), myCrypto.pubkey.q);
          for (int i = 0; i <= rh.degree; i++)
            rh.coef[i] *= myCrypto.pubkey.p;

          struct Poly msg_p = char2poly(str[0]);
          cipher = mod(add(rh, msg_p), myCrypto.pubkey.q);*/
          print_poly(cipher, GET_NAME(cipher));
          tmp = decrypt(cipher,myCrypto.prikey);
          printf("%c",tmp);
        
    }
    E4C_CATCH(RuntimeException){
      printf("Error: %s\n", E4C_EXCEPTION.type->name);
    }
    printf("\n");
    return 0;
}