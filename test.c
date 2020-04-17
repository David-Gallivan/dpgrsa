//JMJ

#include <gmp.h>
#include <stdio.h>
#include "math/blumblumshub.h"
#include "math/largeinteger.h"
#include "math/fermatprimality.h"
#define BASE_TEN 10

const char* mval = "1222333444555666777888999000";


int main(){
  printf("Here goes our first gmp large int test\n");
  mpz_t m;
  mpz_init(m);
  mpz_set_str(m, mval, BASE_TEN);
  gmp_printf("%Zd\n", m);
/*
  printf("Now for some blum blum shub action\n");
  struct bbsFrame* f = bbsInit(7);
  //for( int i = 0; i<10000; i++) printf("%d", bbsBinaryDigit(f));
  int d = bbsBinaryDigit(f);
  char b = bbsByte(f);
  printf("%d %c\n", d, b);

  printf("Now let's get some big random integers!\n");
  mpz_t numero;
  mpz_init(numero);
  //mpz_init_set(numero, nthPowerOfTwo(7));
  nthPowerOfTwo(numero, 32);
  gmp_printf("%Zd\n", numero);
  randomLargeInteger(numero, 88, 7);
  gmp_printf("%Zd\n", numero);
*/
  printf("Time for an 80-decimal-digit integer.\n");
  randomLargeDecimalInteger(m, 80, 13);
  gmp_printf("%Zd\n", m);

  printf("%d\n",isPseudoprime(m));

  printf("Now to find a prime number\n");
  randomLargeDecimalInteger(m, 80, 23);
  int count = 0;
  while(!isPseudoprime(m))
  {
    mpz_add_ui(m, m, 1);
    count++;
  }
  gmp_printf("It took %d tries to find:\n%Zd\n", count, m);
  return 0;
}
