//JMJ

// rsa.h
// by David Gallivan

// Functions for generating keys, encrypting and decrypting
// IN PROGRESS

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>
#include "randomprime.h"
#include "eea.h"
#include "modexp.h"

#define DEFAULT_E "65537"
#define MINIMUM_DIFFERENCE_POWER 95
#define DEBUG 0

// The idea for the key structs is from Andrew Kiluk's library
// Both keys use the same struct
// Separating public/private is the user's responsibility
struct key
{
  mpz_t exp;  // the exponent; for a private key this has the function of 'd'
  mpz_t mod;  // the modulus
};

// generateKeys
// FIXME  documentation
int generateKeys(struct key *pub, struct key *priv, int primeDigits, int seed)
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
  mpz_init_set(pub->exp, e);
  mpz_init_set(priv->exp, d);
  mpz_init_set(pub->mod, n);
  mpz_init_set(priv->mod, n);

  return 0;
}

// encrypt
//
// encrypts m to c with k
int encrypt(struct key *k, mpz_t m, mpz_t c)
{
  mpz_powm_h(c, m, k->exp, k->mod);
  return 0;
}

// decrypt
//
// decrypts c to m with k
// basically equal to encrypt
int decrypt(struct key *k, mpz_t c, mpz_t m)
{
  mpz_powm_h(m, c, k->exp, k->mod);
  return 0;
}
