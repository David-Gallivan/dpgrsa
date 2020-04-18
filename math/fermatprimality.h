//JMJ

// fermatprimality.h

#ifndef __FERMATPRIMALITY_H__
#define __FERMATPRIMALITY_H__

#include <gmp.h>
#include <stdlib.h>

// isPseudoprime
//
// Returns 1 if n is pseudoprime by
//  Fermat's primality test; otherwise
//  returns 0.
int isPseudoprime(mpz_t n)
{
  mpz_t a;
  mpz_init_set_str(a, "2", 10);  //  a=2
  mpz_t nMinusOne;
  mpz_init(nMinusOne);
  mpz_sub_ui(nMinusOne, n, 1);  // n-1
  mpz_t remainder;
  mpz_init(remainder);
  mpz_powm(remainder, a, nMinusOne, n);  //FIXME I need to implement this myself
  if(mpz_cmp_ui(remainder, 1))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

#endif
