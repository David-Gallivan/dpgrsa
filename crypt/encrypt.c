//JMJ

// encrypt.c

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include "readin.c"

#define DEBUG 1

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    printf("usage: encrypt <message> <key>\n");
    return 0;
  }

  // read in the PUBLIC key and the message
  char *message, *eString, *nString;
  message = eString = nString = 0;
  readMessage(argv[1], &message);
  readPublicKey(argv[2], &eString, &nString);

  if (DEBUG) printf("m: %s\ne: %s\nn: %s\n", message, eString, nString);

  // set all the integers
  mpz_t m, e, n, ciphertext;
  mpz_init_set_str(m, message, 10);
  mpz_init_set_str(e, eString, 10);
  mpz_init_set_str(n, nString, 10);
  mpz_init(ciphertext);
  
  // do the exponentiation
  mpz_powm(ciphertext, m, e, n);

  // output
  if (DEBUG) gmp_printf("ciphertext: %Zd\n", ciphertext);
  FILE *fp;
  fp = fopen("ciphertext.txt", "w");
  gmp_fprintf(fp, "%Zd\n", ciphertext);
  fclose(fp);

  return 0;
}
