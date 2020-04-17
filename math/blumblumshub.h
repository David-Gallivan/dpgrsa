//JMJ

// blumblumshub.h

#ifndef __BLUMBLUMSHUB_H__
#define __BLUMBLUMSHUB_H__

#include <stdlib.h>
#include <stdio.h>
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
struct bbsFrame* bbsInit(long int seed)
{
  struct bbsFrame* framePtr = malloc(sizeof(struct bbsFrame));
  mpz_t p;
  mpz_init_set_str(p, bbsPrimeP, 10);
  mpz_t q;
  mpz_init_set_str(q, bbsPrimeQ, 10);
  mpz_init(framePtr->modulus);
  mpz_mul(framePtr->modulus, p, q);
  mpz_init(framePtr->seed);
  mpz_set_ui(framePtr->seed, seed);
  return framePtr;
}

// bbsBinaryDigit
//
// Updates the frame passed in and
//  returns a pseudorandom digit,
//  1 or 0, as an integer.
int bbsBinaryDigit(struct bbsFrame* framePtr)
{
  mpz_t newSeed;
  mpz_init(newSeed);
  mpz_set(newSeed, framePtr->seed);
  mpz_mul(newSeed, newSeed, newSeed);
  mpz_mod(newSeed, newSeed, framePtr->modulus);
  mpz_set(framePtr->seed, newSeed);
  return mpz_odd_p(newSeed);  // return int 1 if odd and 0 if even
}

// bbsByte
//
// Calls bbsDigit 8 times and returns
//  the resulting pseudorandom byte.
char bbsByte(struct bbsFrame* frame)
{
  char byte = 0x0;
  for (int i = 0; i < 8; i++)
  {
    byte += (char) bbsBinaryDigit(frame) << i;
  }
  return byte;
}

// bbsDecimalDigit
//
// Calls bbsByte and manipulates it
//  into an ASCII character 0-9.
char bbsDecimalDigit(struct bbsFrame* framePtr)
{
  char byte = bbsByte(framePtr)&0b00001111;  // set upper 4 bits to 0
  while((int)byte>9)  //ensure that the result is 0-9
  {
    byte = bbsByte(framePtr)&0b00001111;
  }
  byte |= 0b00110000;  // make it an ASCII digit
  //printf("%c\n", byte);
  return byte;
}

#endif
