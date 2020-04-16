//JMJ

// blumblumshub.h

#ifndef __BLUMBLUMSHUB_H__
#define __BLUMBLUMSHUB_H__

#include <stdlib.h>
#include <gmp.h>

const char* bbsPrimeP = "1000003";
const char* bbsPrimeQ = "2001991";

// struct bbsFrame
//
// Contains the modulus n and the
//  current seed x to pass into
//  Blum Blum Shub pseudorandom
//  data generation functions
struct bbsFrame
{
  mpz_t seed;  // Begins as the seed and is updated
  mpz_t modulus;  // The modulus
};

// bbsInit
//
// Initializes a bbsFrame with
//  modulus BBS_PRIME_P * BBS_PRIME_Q
//  and seed specified by caller
struct bbsFrame* bbsInit(long int seed);

// bbsDigit
//
// Updates the frame passed in and
//  returns a pseudorandom digit,
//  1 or 0.
int bbsDigit(struct bbsFrame* framePtr);

// bbsByte
//
// Calls bbsDigit 8 times and returns
//  the resulting pseudorandom byte.
char bbsByte(struct bbsFrame* frame);

#endif
