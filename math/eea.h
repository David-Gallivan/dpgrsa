//JMJ

// eea.h

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1 // set this to 1 to print out the chart while running the algorithm

struct eeaResults {
  mpz_t gcd;
  mpz_t x;  //ax+by=gcd
  mpz_t y;
  int rounds;  // the number of rounds it took;
};

// mpz_extendedEuclideanAlgorithm
struct eeaResults* mpz_extendedEuclideanAlgorithm(mpz_t a, mpz_t b)
{
  // initialize results struct
  struct eeaResults* results = malloc(sizeof(struct eeaResults));
  mpz_init(results->gcd);
  mpz_init(results->x);
  mpz_init(results->y);

  // if a==b, gcd is a, x is 1, y is 0
  if (mpz_cmp(a, b) == 0)
  {
    mpz_set(results->gcd, a);
    mpz_set_ui(results->x, 1);
    mpz_set_ui(results->y, 0);
    return results;
  }
  if (mpz_cmp(a, b) < 0)  // we want a > b
  {
    mpz_swap(a, b);
  }

  // chart column headers
  if (DEBUG) gmp_printf("i\tr\tq\tx\ty\n");

  // row 0
  mpz_t rpp, xpp, ypp;  // pp means "previous to previous" or "two before"
  mpz_init_set(rpp, a);						// rpp = a
  mpz_init_set_si(xpp, 1);					// xpp = 1
  mpz_init_set_si(ypp, 0);					// ypp = 0
  if (DEBUG) gmp_printf("0\t%Zd\t \t%Zd\t%Zd\n", rpp, xpp, ypp);

  // row 1
  mpz_t rp, qp, xp, yp; // initializing; p means "previous"
  mpz_init_set(rp, b);						// rp = b
  mpz_init(qp);							// qp = a // b
  mpz_fdiv_q(qp, a, b);
  mpz_init_set_ui(xp, 0);					// xp = 0
  mpz_init_set_ui(yp, 1);					// yp = 1
  if (DEBUG) gmp_printf("1\t%Zd\t%Zd\t%Zd\t%Zd\n", rp, qp, xp, yp);

  // row 2 : the first round of computations for the algorithm
  int i = 2;                                                    // i = 2 (the row index)
  mpz_t r, q, x, y, product;
  mpz_init(r); mpz_init(q); mpz_init(x); mpz_init(y); mpz_init(product);
  mpz_mod(r, rpp, rp);						// r = rpp % rp
  if (mpz_cmp_ui(r, 0))  					// if r!=0:
  {								//   q = rp // r
    mpz_fdiv_q(q, rp, r);
  }
  mpz_mul(product, qp, xp);					// x = xpp - qp * xp
  mpz_sub(x, xpp, product);
  mpz_mul(product, qp, yp);					// y = ypp - qp * yp
  mpz_sub(y, ypp, product);

  // print row i, work on row i+1
  while (mpz_cmp_ui(r, 0))					// while r!= 0:
  {
    if (DEBUG) gmp_printf("%d\t%Zd\t%Zd\t%Zd\t%Zd\n", i, r, q, x, y);
    i++;					//   y = ypp - qp * yp
    if (i < 0) break;  // this means the unthinkable has happened!
    
    // update "previous" values
    mpz_set(rpp, rp);
    mpz_set(rp, r);
    mpz_set(qp, q);
    mpz_set(xpp, xp);
    mpz_set(xp, x);
    mpz_set(ypp, yp);
    mpz_set(yp, y);
    
    // repeat steps for row 2 (above)
    mpz_mod(r, rpp, rp);
    if (mpz_cmp_ui(r, 0))
    {
      mpz_fdiv_q(q, rp, r);
    }
    mpz_mul(product, qp, xp);
    mpz_sub(x, xpp, product);
    mpz_mul(product, qp, yp);
    mpz_sub(y, ypp, product);
  }
  if (DEBUG) gmp_printf("%d\t%Zd\n", i, r);

  // set the results and return!
  mpz_set(results->gcd, rp);
  mpz_set(results->x, xp);
  mpz_set(results->y, yp);
  results->rounds = i - 2;
  return results;
}
