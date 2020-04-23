//JMJ

// fermatprimality.h
// by David Gallivan

// offers the function "isPseudoprime"

#ifndef __FERMATPRIMALITY_H__
#define __FERMATPRIMALITY_H__

#include <gmp.h>
#include <stdlib.h>
#include "modexp.h"

// isPseudoprime
//
// Returns 1 if n is pseudoprime by
//  Fermat's primality test; otherwise
//  returns 0.
int isPseudoprime(mpz_t n)
{
  mpz_t a;  // a is the base, which will be set to 2
  mpz_init_set_str(a, "2", 10);
  mpz_t nMinusOne;  // nMinusOne: n-1
  mpz_init(nMinusOne);
  mpz_sub_ui(nMinusOne, n, 1);
  mpz_t remainder;  // remainder: a to the power nMinusOne mod n
  mpz_init(remainder);
  mpz_powm_h(remainder, a, nMinusOne, n);
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
