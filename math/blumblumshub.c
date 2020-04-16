//JMJ

// blumblumshub.c

#include "blumblumshub.h"

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

// bbsDigit
//
// Updates the frame passed in and
//  returns a pseudorandom digit,
//  1 or 0.
int bbsDigit(struct bbsFrame* framePtr)
{
  mpz_t newSeed;
  mpz_init(newSeed);
  mpz_set(newSeed, framePtr->seed);
  mpz_mul(newSeed, newSeed, newSeed);
  mpz_mod(newSeed, newSeed, framePtr->modulus);
  mpz_set(framePtr->seed, newSeed);
  return mpz_odd_p(newSeed);
  //FIXME in the process of gmpizing this func, and the next one

  //long int  = (framePtr->x*framePtr->x)%(framePtr->n);
  //return framePtr->x%2;
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
    byte += (char) bbsDigit(frame) << i;
  }
  return byte;
}
