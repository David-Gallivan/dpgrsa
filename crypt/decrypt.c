//JMJ

// decrypt.c

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

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
  size_t cLength, eLength, nLength, dLength;
  FILE *fp, *copy;
  printf("-1");
  copy = fp = fopen(argv[1], "r");
  printf("0");
  getline(&ciphertext, &cLength, fp);
  fclose(copy);
  printf("1");
  fp = fopen(argv[2], "r");
  getline(&eString, &eLength, fp);
  fp = fp;
  getline(&nString, &nLength, fp);
  fclose(fp);
  printf("2");
  fp = fopen(argv[3], "r");
  getline(&dString, &dLength, fp);
  fclose(fp);
  printf("3");

  if (DEBUG) printf("read everything\n");

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
  fp = fopen("decryptedmessage", "w");
  gmp_fprintf(fp, "%Zd\n", m);
  fclose(fp);

  return 0;
}
