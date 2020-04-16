//JMJ

#include <gmp.h>
#include <stdio.h>
#include "math/blumblumshub.c"
//#include "math/largeinteger.h"
#define BASE_TEN 10

const char* mval = "1222333444555666777888999000";


int main(){
  printf("Here goes our first gmp large int test\n");
  mpz_t m;
  mpz_init(m);
  mpz_set_str(m, mval, BASE_TEN);
  gmp_printf("%Zd\n", m);

  printf("Now for some blum blum shub action\n");
  struct bbsFrame* f = bbsInit(7);
  for( int i = 0; i<1000; i++) printf("%d", bbsDigit(f));
  int d = bbsDigit(f);
  char b = bbsByte(f);
  printf("%d %c\n", d, b);
/*
  printf("Now let's get some big random integers!\n");
  mpz_t numero;
  mpz_init(numero);
  mpz_init_set(numero, nthPowerOfTwo(7));
  gmp_printf("%Zd\n", numero);
  mpz_init_set(numero, randomLargeInteger(9, 7));
  gmp_printf("%Zd\n", numero);
*/

  return 0;
}
