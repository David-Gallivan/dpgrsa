//JMJ

// decrypt.c

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "readin.c"

#define DEBUG 1

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
  mpz_powm(m, c, d, n);

  // output
  if (DEBUG) gmp_printf("message: %Zd\n", m);
  FILE *fp;
  fp = fopen("decryptedmessage.txt", "w");
  gmp_fprintf(fp, "%Zd\n", m);
  fclose(fp);

  return 0;
}
