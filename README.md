JMJ

dpgrsa
An implemetation of the RSA cryptosystem
by David Patrick Gallivan

The ultimate hope of the project is to become a C/C++ library providing
RSA functionality that is reliable and efficient enough to utilize in 
various kinds of projects but simple enough to be used as a demonstration
of RSA, e.g. for students. GMP's multiple precision integers are used so
that the keys can be of very large size, unlike many demonstrations of RSA
that can be found online.

This project began to fulfill several academic requirements in Spring 2020:
First, assignment 7 of Dr. Truszczynski's CS378.
Second, the project to use for CS395.

To test the project, run "make run". All needed binaries will be compiled
and run, and the results will be stored in the results directory.

GMP has to be installed on the machine for this project to compile. All
the algorithms are implemented in header files in the "alg" directory,
and they can be taken and used for other projects as desired. Please credit
this repository in your documentation if you use the code.

Though I have done my best to make this all work reliably and usefully, I
make no guarantees thereof. I would be glad to hear from anyone who has
questions or suggestions.

Known issues to fix as of April 2020:
 - The Makefile needs help... besides being tacky and amateur in general,
    it needs targets to compile .so and .a libraries.
 - Certain mathematical functions (see the alg directory) are homemade
    and have not been thoroughly tested; however, they are available for
    export.
 - It would be desirable to add the Miller-Rabin primality test for
    increased certainty of primality, over and above the Fermat test.
 - It might be expedient to use GMP's modular exponentiation function
    rather than the homemade one in this repository for reliability and
    speed; thorough testing would verify the difference. The homemade one
    was hand-coded because this began as an academic assignment. To switch
    to GMP's, open "rsa.h" and change every instance of "mpz_modx_h" to
    "mpz_modx".
 - Some regular ints are used here and there, particularly in eea.h, that
    technically prevent the precision from being arbitrary. For
    ordinary cryptographic purposes, they should never overflow, but it
    might be good to convert these to mpz types just in case.
 - The public key exponent should be made chooseable, or at least its
    length should; currently, it is 65537. So n has to be bigger.
 - The length of p and q should be able to be chosen in binary as well
    as in decimal digits.
 - As pointed out by Dr. T's grader, Nathan Arnold, several random bases
    ought to be used for Fermat's primality test rather than just one;
    the test is valid with just one, but we can have more confidence in
    it if we use more than one.
 - Testing shows that p and q can be up to at least 500 decimal digits
    before the system fails. 600 decimal digits for p and q makes it
    unreliable; too much larger than that crashes it. This means keys are
    over 3,000 bits, but not quite 4096.
