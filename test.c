//JMJ

#include <gmp.h>
#include <stdio.h>
#define BASE_TEN 10

const char* mval = "1222333444555666777888999000";


int main(){
  mpz_t m;
  mpz_init(m);
  mpz_set_str(m, mval, BASE_TEN);
  gmp_printf("%Zd\n", m);
}
