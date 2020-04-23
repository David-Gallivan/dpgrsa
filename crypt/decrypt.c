//JMJ

// decrypt.c
// by David Gallivan

// Decrypts an RSA ciphertext.
// Ciphertext input must be a file with a single
// base-10 integer in ASCII characters.
// Public key input must be a file with two such
// integers, separated by any character.
// Private key input must be a file with one such integer.
// Output will be "decrypted_message.txt"

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "readin.c"
#include "../math/modexp.h"

#define DEBUG 0

int main(int argc, char** argv)
{
  if (argc != 4)
  {
    printf("usage: dec <ciphertext> <public_key> <private_key>");
    return 0;
  }

  if (DEBUG) printf("about to read everything\n");

  // read in the keys and ciphertext
  char *ciphertext, *eString, *nString, *dString;
  ciphertext = 0;  //initializing to get rid of the warning
  eString = 0;
  nString = 0;
  dString = 0;
  readMessage(argv[1], &ciphertext);
  readPublicKey(argv[2], &eString, &nString);
  readPrivateKey(argv[3], &dString);


  if (DEBUG) printf("c: %s\ne: %s\nn: %s\nd: %s\n", ciphertext, eString, nString, dString);

  // set all the integers
  mpz_t c, e, n, d, m;
  mpz_init_set_str(c, ciphertext, 10);
  mpz_init_set_str(e, eString, 10);
  mpz_init_set_str(n, nString, 10);
  mpz_init_set_str(d, dString, 10);
  mpz_init(m);

  if (DEBUG) printf("ints all set\n");

  // do the exponentiation
  mpz_powm_h(m, c, d, n);

  // output
  if (DEBUG) gmp_printf("message: %Zd\n", m);
  FILE *fp;
  fp = fopen("decrypted_message.txt", "w");
  gmp_fprintf(fp, "%Zd\n", m);
  fclose(fp);

  return 0;
}
