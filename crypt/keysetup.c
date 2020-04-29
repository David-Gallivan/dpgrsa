//JMJ

// keySetup.c
// by David Gallivan

// Generates public and private keys for RSA.
// Outputs public key to a file "public_key.txt" as
// two base-ten numbers separated by a newline,
// the first being e and the second n.
// Outputs d to a file "private_key.txt".
// Takes one optional command line argument, a seed
// for the pseudorandom generator.

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include "../math/randomprime.h"
#include "../math/eea.h"

#include "rsa.h"

#define DEFAULT_DIGITS 100
#define DEFAULT_SEED 7
#define DEFAULT_E "65537"
#define MINIMUM_DIFFERENCE_POWER 95//FIXME
#define DEBUG 0 

int main(int argc, char** argv)
{
  int digits, seed;
  //process command line arguments
  if (argc != 2)  //TODO make more options
  {
    digits = DEFAULT_DIGITS;
    seed = DEFAULT_SEED;
  }
  if (argc == 2)  //TODO make the digits adjustable
  {
    digits = DEFAULT_DIGITS;
    if ( (seed=atoi(argv[1]))<=0 )
    {
      printf("Bad arg; setting seed=7\n");
      seed = DEFAULT_SEED;
    }
  }

  // Generate the key
  struct publicKey *pu = malloc(sizeof(struct publicKey));
  struct privateKey *pr = malloc(sizeof(struct privateKey));
  generateKeys(pu, pr, digits, seed);

  //write it all out!
  //if (DEBUG) gmp_printf("e: %Zd\nd: %Zd\nn: %Zd\n", e, d, n);
  FILE *fp;
  fp = fopen("public_key.txt", "w+");
  gmp_fprintf(fp, "%Zd\n%Zd\n", pu->e, pu->n);
  fclose(fp);
  fp = fopen("private_key.txt", "w+");
  gmp_fprintf(fp, "%Zd\n", pr->d);


/*
  // generate p
  mpz_t p;
  mpz_init(p);
  randomPrime(p, digits, seed);
  
  // generate q, making sure |p-q| > 10tothe95
  mpz_t q, difference, minDiff;
  mpz_init(q); mpz_init(difference); mpz_init(minDiff);
  mpz_ui_pow_ui(minDiff, 10, MINIMUM_DIFFERENCE_POWER);
  do
  {
    seed++;
    randomPrime(q, digits, seed);
    mpz_sub(difference, p, q);
    mpz_abs(difference, difference);
  } while (mpz_cmp(difference, minDiff) < 0);


  // compute n
  mpz_t n;
  mpz_init(n);
  mpz_mul(n, p, q);

  // choose e relatively prime to (p-1)(q-1)
  mpz_t pMinusOne, qMinusOne, product, e;
  mpz_init(pMinusOne), mpz_init(qMinusOne), mpz_init(product), mpz_init(e);
  mpz_sub_ui(pMinusOne, p, 1); mpz_sub_ui(qMinusOne, q, 1);
  mpz_mul(product, pMinusOne, qMinusOne);
  mpz_set_str(e, DEFAULT_E, 10);
  while (!mpz_relativelyPrime(e, product))  // increment e until it works
  {
    mpz_add_ui(e, e, 1);
  }

  // compute d
  mpz_t d;
  mpz_init(d);
  int fail = mpz_modularInverse(d, e, product);  // product is (p-1)(q-1)
  if (fail) return 1;

  //write it all out!
  if (DEBUG) gmp_printf("e: %Zd\nd: %Zd\nn: %Zd\n", e, d, n);
  FILE *fp;
  fp = fopen("public_key.txt", "w+");
  gmp_fprintf(fp, "%Zd\n%Zd\n", e, n);
  fclose(fp);
  fp = fopen("private_key.txt", "w+");
  gmp_fprintf(fp, "%Zd\n", d);
*/

  return 0;
}
