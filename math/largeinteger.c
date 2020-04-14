//JMJ

// largeinteger.c

#include <largeIntegers.h>

// nthPowerOfTwo
int nthPowerOfTwo(mpz_t power, int n)
{
  char* initString = malloc(n+1);
  memset(initString, ASCII_ONE, 1);
  memset(initString + 1, ASCII_ZERO, n);
  mpz_init_set_str(power, initString, BASE_TWO);
  return 0;
}

// randomLargeInteger
int randomLargeInteger(mpz_t x, int n, int seed)
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
  mpz_init_set_str(x, initString, BASE_TWO);
  return 0;
}

