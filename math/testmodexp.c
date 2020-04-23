//JMJ

// testme.c

#include <stdio.h>
#include <gmp.h>
#include "modexp.h"

int main(int argc, char **argv)
{
  mpz_t result, b, x, n;
  mpz_init(result);
  mpz_init_set_str(b, argv[1], 10);
  mpz_init_set_str(x, argv[2], 10);
  mpz_init_set_str(n, argv[3], 10);
  mpz_powm_h(result, b, x, n);
  gmp_printf("%Zd to the power of %Zd modulo %Zd is %Zd\n", b, x, n, result);
  return 0;
}
