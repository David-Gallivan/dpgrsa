//JMJ

// blumblumshub.h

#ifndef __BLUMBLUMSHUB_H__
#define __BLUMBLUMSHUB_H__

#include <stdlib.h>

#define BBS_PRIME_P 1000003
#define BBS_PRIME_Q 2001991

// struct bbsFrame
//
// Contains the modulus n and the
//  current seed x to pass into
//  Blum Blum Shub pseudorandom
//  data generation functions
struct bbsFrame
{
  long int x;
  long int n;
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
int bbsDigit(struct bbsFrame* frame);

// bbsByte
//
// Calls bbsDigit 8 times and returns
//  the resulting pseudorandom byte.
char bbsByte(struct bbsFrame* frame);

#endif
