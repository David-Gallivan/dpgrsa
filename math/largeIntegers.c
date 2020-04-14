//JMJ

// largeprimes.c

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
mpz_t nthPowerOfTwo(int n)
{
  char* initString = malloc(n+1);
  memset(initString, ASCII_ONE, 1);
  memset(initString + 1, ASCII_ZERO, n);
  mpz_t power;
  mpz_init_set_str(power, initString, BASE_TWO);
  return power
}

// randomLargeInteger
//
// Given a power of 2 n, returns
// a rando integer greater than 2
// to the n and less than 2 to the
// n+1. Return type is mpz_t.
mpz_t randomLargeInteger(int n, int seed)
{
  struct bbsFrame* frame = bbsInit(seed);
  char* initString = malloc(n+1);
  memset(initString, ASCII_ONE, 1);
  for (int i = 0; i < n; i++)
  {
    digit = bbsDigit(frame);
    if (digit)
    {
      memset(initString+1+i, ASCII_ONE, 1);
    }
    else
    {
      memset(initString+1+i, ASCII_TWO, 1);
    }
  }
  mpz_t x;
  mpz_init_set_str(x, initString, BASE_TWO);
  return x;
}

