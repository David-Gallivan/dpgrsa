//JMJ

// largeinteger.h

#ifndef __LARGEINTEGERS_H__
#define __LARGEINTEGERS_H__

#include <gmp.h>
#include <stdlib.h>
#include "blumblumshub.h"

#define BASE_TWO 2
#define BASE_TEN 10
#define ASCII_ZERO 0x30
#define ASCII_ONE 0x31

// nthPowerOfTwo
//
// sets "power" to 2 to the power n
int nthPowerOfTwo(mpz_t power, int n);

// randomLargeInteger
//
// sets x to a random integer greater than or
// equal to 2 to the n, less than 2 to the n-1,
// using Blum Blum Shub with seed "seed"
int randomLargeInteger(mpz_t x, int n, int seed);

#endif
