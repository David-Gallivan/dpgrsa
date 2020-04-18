//JMJ

// randomprime.h

#ifndef __RANDOMPRIME_H__
#define __RANDOMPRIME_H__

#include <gmp.h>
#include <stdlib.h>
#include "fermatprimality.h"
#include "largeinteger.h"

// randomPrime
//
// Sets x to a random prime number
//  with at least n decimal digits
//  using specified BBS seed; returns
//  the number of tries it took
int randomPrime(mpz_t x, int n, int seed)
{
  randomLargeDecimalInteger(x, n, seed);
  int tries = 0;
  while(!isPseudoprime(x))
  {
    mpz_add_ui(x, x, 1);
    tries++;
  }
  return tries;
}

#endif
