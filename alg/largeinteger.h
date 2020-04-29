//JMJ

// largeinteger.h
// by David Gallivan

// functions for generating large pseudorandom integers

#ifndef __LARGEINTEGERS_H__
#define __LARGEINTEGERS_H__

#include <gmp.h>
#include <stdlib.h>
#include <string.h>
#include "blumblumshub.h"

#define BASE_TWO 2
#define BASE_TEN 10
#define ASCII_ZERO 0x30
#define ASCII_ONE 0x31

// nthPowerOfTwo
//
// sets "power" to 2 to the power n
int nthPowerOfTwo(mpz_t power, int n)
{
  char* initString = malloc(n+1);
  memset(initString, ASCII_ONE, 1);  // we begin a string with a '1'
  memset(initString + 1, ASCII_ZERO, n);  // and fill the rest with zeroes
  mpz_init_set_str(power, initString, BASE_TWO);
  return 0;
}



// randomLargeInteger
//
// sets x to a random integer greater than or
// equal to 2 to the n, less than 2 to the n-1,
// using Blum Blum Shub with seed "seed"
int randomLargeInteger(mpz_t x, int n, int seed)
{
  struct bbsFrame* frame = bbsInit(seed);
  char* initString = malloc(n+1);
  memset(initString, ASCII_ONE, 1);  // we set the first char of the string to '1'
  for (int i = 0; i < n; i++)        // and fill the rest with random ones and zeros
  {
    int digit = bbsBinaryDigit(frame);
    if (digit)
    {
      memset(initString+1+i, ASCII_ONE, 1);
    }
    else
    {
      memset(initString+1+i, ASCII_ZERO, 1);
    }
  }
  mpz_init_set_str(x, initString, BASE_TWO);
  return 0;
}

// randomLargeDecimalInteger
//
// sets x to a random integer with at least
//  n decimal digits with BBS seed "seed"
int randomLargeDecimalInteger(mpz_t x, int n, int seed){
  struct bbsFrame* framePtr = bbsInit(seed);
  char* initString = malloc(n+2);
  // Set the first digit to be nonzero
  char b = bbsDecimalDigit(framePtr);
  while (b == '0')
  {
    b = bbsDecimalDigit(framePtr);
  }
  memset(initString, (int) b, 1);
  // Set the rest of the digits
  for (int i = 0; i < n; i++)
  {
    b = bbsDecimalDigit(framePtr);
    memset(initString+1+i, (int) b, 1);
  }
  memset(initString+n+1, 0, 1);
  //printf("%s",initString);
  mpz_init_set_str(x, initString, BASE_TEN);
  return 0;
}



#endif
