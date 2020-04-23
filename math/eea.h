//JMJ

// eea.h
// by David Gallivan

// functions for running the Extended Euclidean Algorithm
// and for computing modular inverses

#ifndef __EEA_H__
#define __EEA_H__

#include <gmp.h>
#include <stdlib.h>
#include <stdio.h>

#define DEBUG 0

struct eeaResults {
  mpz_t gcd;  // the greatest common denominator
  mpz_t x;  // x and y are integers such that ax+by=gcd
  mpz_t y;
  int rounds;  // the number of rounds it took
};

// mpz_extendedEuclideanAlgorithm
//
// given to mpz integers A and B, runs the EEA on them and returns
// a pointer to an eeaResults structure with the results. In debug
// mode, it prints out the chart showing all its steps. Some lines
// are commented with the python code from which they were
// translated (also my own original work).
struct eeaResults* mpz_extendedEuclideanAlgorithm(mpz_t A, mpz_t B)
{
  // initialize results struct
  struct eeaResults* results = malloc(sizeof(struct eeaResults));
  mpz_init(results->gcd);
  mpz_init(results->x);
  mpz_init(results->y);

  //copy the inputs so they don't get changed
  mpz_t a, b;
  mpz_init_set(a, A);
  mpz_init_set(b, B);
  
  // if one input is zero, no-can-do
  if(mpz_cmp_ui(a, 0)==0||mpz_cmp_ui(b, 0)==0)
  {
    if (DEBUG) gmp_printf("Fail! We don't do zeroes here!\n");
    results->rounds = -1;  // failure indicated by a negative number of rounds
    return results;
  }

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

  // row 0: here we start setting some rolling variables
  mpz_t rpp, xpp, ypp;  // pp means "previous to previous" or "two before"
  mpz_init_set(rpp, a);						// rpp = a
  mpz_init_set_si(xpp, 1);					// xpp = 1
  mpz_init_set_si(ypp, 0);					// ypp = 0
  if (DEBUG) gmp_printf("0\t%Zd\t \t%Zd\t%Zd\n", rpp, xpp, ypp);

  // row 1 : setting more rolling varialbles
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

// mpz_relativelyPrime
//
// returns 1 if x and y are relatively prime
//  otherwise returns 0
// NOTE: This does not check for EEA errors./
int mpz_relativelyPrime(mpz_t x, mpz_t y)
{
  struct eeaResults* results = mpz_extendedEuclideanAlgorithm(x, y);
  if (results->rounds<0)
  {
    if (DEBUG) printf("EEA failed.\n");
    return 1;
  }
  if (mpz_cmp_ui(results->gcd, 1)==0)  // if gcd == 1
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// mpz_modularInverse
//
// sets a1 to the modular invers of a mod n, if possible
int mpz_modularInverse(mpz_t a1, mpz_t a, mpz_t n)
{
  // initialize and check for bad input
  mpz_t aModN;  // aModN is a mod n
  mpz_init(aModN);
  if (DEBUG) gmp_printf("Taking %Zd mod %Zd\n", a, n);
  mpz_mod(aModN, a, n);
  if (mpz_cmp(aModN, n) == 0)  // if a = n (mod n)
  {
    if (DEBUG) printf("a congruent to n: there is no inverse!\n");
    return 1;
  }

  // run the EEA
  struct eeaResults* results = mpz_extendedEuclideanAlgorithm(a, n);
  if (results->rounds<0)
  {
    if (DEBUG) printf("EEA failed.\n");
    return 1;
  }
  if (mpz_cmp_ui(results->gcd, 1))  // if gcd != 0
  {
    if (DEBUG) printf("a and n not relatively prime: there is no inverse!\n");
    return 1;
  }

  // determine whether x or y gives the inverse
  mpz_t xModN, yModN, xa, ya, xan, yan;  // intermediate variables for the math
  mpz_init(xModN); mpz_init(yModN); mpz_init(xa); mpz_init(ya); mpz_init(xan); mpz_init(yan);
  mpz_mod(xModN, results->x, n);
  mpz_mul(xa, xModN, aModN);
  mpz_mod(xan, xa, n);
  mpz_mod(yModN, results->y, n);
  mpz_mul(ya, yModN, aModN);
  mpz_mod(yan, ya, n);
  if (DEBUG) gmp_printf("xan, yan: %Zd %Zd\n", yModN, ya, yan);
  if (mpz_cmp_ui(xan, 1)==0)  // xan is (x*a)%n
  {
    if (DEBUG) gmp_printf("found it! %Zd\n", xModN);
    mpz_set(a1, xModN);  // xModN is x%n
  }
  else if (mpz_cmp_ui(yan, 1)==0)   // yan is (y*a)%n
  {
    if (DEBUG) gmp_printf("found it! %Zd\n", yModN);
    mpz_set(a1, yModN);  // yModN is y%n
  }
  else
  {
    if (DEBUG) printf("something is seriously wrong here.\n");
    mpz_set_ui(a1, -1);
    return 1;
  }

  return 0;
}

#endif
