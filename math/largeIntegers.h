//JMJ

// largeIntegers.h

#ifndef __LARGEINTEGERS_H__
#define __LARGEINTEGERS_H__

#include <gmp.h>
#include <stdlib>
#include "blumblumshub.c"

#define BASE_TWO 2
#define BASE_TEN 10
#define ASCII_ZERO 0x30
#define ASCII_ONE 0x31

// nthPowerOfTwo
//
// Given power n, returns two to the n
//  as an mpz_t
mpz_t nthPowerOfTwo(int n);

// randomLargeInteger
//
// Given a power of 2 n, returns
// a rando integer greater than 2
// to the n and less than 2 to the
// n+1. Return type is mpz_t.
mpz_t randomLargeInteger(int n, int seed);

#endif
