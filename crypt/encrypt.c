//JMJ

// encrypt.c

#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>

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
  size_t mLength, eLength, nLength;
  FILE* fp;
  if (DEBUG) printf("about to read stuff\n");
  fp = fopen(argv[1], "r");
  getline(&message, &mLength, fp);
  fclose(fp);
  if (DEBUG) printf("message read: %s\n", message);
  fp = fopen(argv[2], "r");
  getline(&eString, &eLength, fp);
  getline(&nString, &nLength, fp);
  fclose(fp);
  if (DEBUG) printf("key read\n");

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
  fp = fopen("ciphertext", "w");
  gmp_fprintf(fp, "%Zd\n", ciphertext);
  fclose(fp);

  return 0;
}
