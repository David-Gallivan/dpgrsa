//JMJ

// modinv.c

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include "../math/eea.h"


int main(int argc, char** argv)
{
  if (argc != 3)
  {
    printf("Need 2 int args!\n");
    return 0;
  }
  mpz_t a, a1, n;
  mpz_init(a); mpz_init(a1); mpz_init(n);
//  printf("stuffs initted\n");
  unsigned long int A = (unsigned long int) atoi(argv[1]);
  unsigned long int N = (unsigned long int) atoi(argv[2]);
  mpz_set_ui(a, A);
  mpz_set_ui(n, N);
//  printf("args gotten\n");
  mpz_modularInverse(a1, a, n);
  gmp_printf("The inverse of %Zd (mod %Zd) is %Zd\n", a, n, a1);
  return 0;
}
