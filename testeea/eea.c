//JMJ

// eea.c

#include <stdio.h>
#include <gmp.h>
#include "../math/eea.h"

int main(int argc, char** argv)
{
  if(argc!=3)
  {
    printf("Two int args, please!\n");
  }
  else
  {
    int aint = atoi(argv[1]);
    int bint = atoi(argv[2]);
    mpz_t a; mpz_init_set_ui(a, (unsigned long int) aint);
    mpz_t b; mpz_init_set_ui(b, (unsigned long int) bint);
    struct eeaResults* res = mpz_extendedEuclideanAlgorithm(a, b);
    gmp_printf("Results: gcd:%Zd, x:%Zd, y:%Zd, rounds:%d\n",
		    res->gcd, res->x, res->y, res->rounds);
  }
  return 0;
}
