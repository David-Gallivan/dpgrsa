//JMJ

// modexp.H
// by David Gallivan

// homemade modular exponentiation

// patterned on pages 78-79 of Trappe & Washington's
// "Introduction to Cryptography with Coding Theory"
// Second Ed.

#ifndef __MODEXP_H__
#define __MODEXP_H__

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEBUG 0

// mpz_powm_h
//
// Sets 'rop' to 'base' to the power 'exp' modulo 'mod'.
// Inputs and outputs are the same as the gmp function
// 'mpz_powm', and the functionality should be equivalent.
// However, negative 'exp' is not supported.
void mpz_powm_h(mpz_t rop, mpz_t base, mpz_t exp, mpz_t mod)  //the h stands for homemade
{
  // Check inputs for validity
  if ( mpz_cmp_ui(exp, 0) < 0)
  {
    if (DEBUG) gmp_printf("failure! exp<0\n");
    return;
  }

  // First we get the exponent in binary
  char* binstr = NULL;  // binstr: the binary string of the exponent
  binstr = mpz_get_str(binstr, 2, exp);
  if (DEBUG) gmp_printf("exponent in binary: %s\n", binstr);

  // Now we get variables ready for running the algorithm's loop
  int maxPwr = strlen(binstr) - 1;  // maxPwr: the biggest power of 2 in the exponent
  mpz_set_ui(rop, 1);  // initialize rop to 1
  mpz_t pB;  // pB: the current power of the base
  mpz_init_set(pB, base);  // pB is now just the base
  int p2;  // p2: the current power of 2

  // Now for each power of 2, we find the base to that exponent
  // mod 'mod' and, if appropriate, multiply it with the total.
  // We traverse binstr from right to left.
  for ( p2 = maxPwr ; p2 >= 0 ; p2 -= 1)
  {
    if (binstr[p2]=='1')
    {
      mpz_mul(rop, rop, pB);
      mpz_mod(rop, rop, mod);
    }
    mpz_mul(pB, pB, pB);  // pB is squared; its exponent going up by powers of two
    mpz_mod(pB, pB, mod);
  }
}

#endif
