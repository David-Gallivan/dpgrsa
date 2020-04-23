//JMJ

// encrypt.c
// by David gallivan

// Encrypts a message with an RSA public key.
// Message input must be a file with a single
// base-10 integer in ASCII characters.
// Key input must be two such integers separated
// by any character.
// Output will be "ciphertext.txt"

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "readin.c"
#include "../math/modexp.h"

#define DEBUG 0

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    printf("usage: encrypt <messagefile> <keyfile>\n");
    return 0;
  }

  // read in the PUBLIC key and the message
  char *message, *eString, *nString;
  message = eString = nString = 0;

  if (DEBUG) printf("about to read message\n");
  readMessage(argv[1], &message);
  if (DEBUG) printf("about to read key\n");
  readPublicKey(argv[2], &eString, &nString);

  if (DEBUG) printf("m: %s\ne: %s\nn: %s\n", message, eString, nString);

  // set all the integers
  mpz_t m, e, n, ciphertext;
  mpz_init_set_str(m, message, 10);
  mpz_init_set_str(e, eString, 10);
  mpz_init_set_str(n, nString, 10);
  mpz_init(ciphertext);
  
  // do the exponentiation
  mpz_powm_h(ciphertext, m, e, n);

  // output
  if (DEBUG) gmp_printf("ciphertext: %Zd\n", ciphertext);
  FILE *fp;
  fp = fopen("ciphertext.txt", "w");
  gmp_fprintf(fp, "%Zd\n", ciphertext);
  fclose(fp);

  return 0;
}
