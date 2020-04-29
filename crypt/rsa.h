//JMJ

// rsa.h
// by David Gallivan

// Functions for generating keys, encrypting and decrypting
// IN PROGRESS

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_E "65537"
#define MINIMUM_DIFFERENCE_POWER 95
#define DEBUG 0

// The idea for the key structs is from Andrew Kiluk's library
struct publicKey
{
  mpz_t e;  // the exponent
  mpz_t n;  // the modulus
};

struct privateKey
{
  mpz_t d;  // the exponent
  mpz_t n;  // the modulus
};

// generateKeys
// FIXME  documentation
int generateKeys(struct publicKey *pub, struct privateKey *priv, int primeDigits, int seed)
{
  // generate p
  mpz_t p;
  mpz_init(p);
  randomPrime(p, primeDigits, seed);

  // generate q, making sure |p-q| > 10tothe95
  mpz_t q, difference, minDiff;
  mpz_init(q); mpz_init(difference); mpz_init(minDiff);
  mpz_ui_pow_ui(minDiff, 10, MINIMUM_DIFFERENCE_POWER);
  do
  {
    seed++;
    randomPrime(q, primeDigits, seed);
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
  if (fail) return 1;  // this occurs if the EEA fails somehow

  // write to the structs
  mpz_init_set(pub->e, e);
  mpz_init_set(priv->d, d);
  mpz_init_set(pub->n, n);
  mpz_init_set(priv->n, n);

  return 0;
}
