//JMJ

// blumblumshub.c

#include <stdlib.h>

const int BBS_PRIME_P = 1000003;
const int BBS_PRIME_Q = 2001991;

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
struct bbsFrame* bbsInit(long int seed)
{
  struct bbsFrame* frame = malloc(sizeof(struct bbsFrame));
  frame->n = BBS_PRIME_P * BBS_PRIME_Q;
  frame->x = seed;
  return frame;
}

// bbsDigit
//
// Updates the frame passed in and
//  returns a pseudorandom digit,
//  1 or 0.
int bbsDigit(struct bbsFrame* frame)
{
  frame->x = (frame->x*frame->x)%(frame->n);
  return frame->x%2;
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
    byte += bbsDigit(frame) << i;
  }
  return byte;
}
