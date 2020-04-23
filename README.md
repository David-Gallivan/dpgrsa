JMJ
dpgrsa
A C library to implement the RSA cryptosystem
by David Patrick Gallivan

The ultimate destiny of the project is to become a C/C++ library providing
RSA functionality. It will hopefully be a useful alternative to a similar
GitHub repository by andrewkiluk which provides RSA key generation,
encryption, and decryption, but is prone to integer overflows (as of Jun
2018). This project resolves that issue by using GMP's multiple precision
integers.

This project began to fulfill several academic requirements in Spring 2020:
First, assignment 7 of Dr. Truszczynski's CS378.
Second, the project to use for CS395.

To test the project, run "make run". All needed binaries will be compiled
and run, and the results will be stored in the results directory.

Known issues to fix as of April 2020:
 - The Makefile needs help
 - The i/o and args are limited to the scope of Dr. T's assignment
 - Currently, key generation, encryption, and decryption cannot be
    exported; they compile into proof-of-concept binaries.
 - Certain mathematical functions (see the math directory) are homemade
    and have not been thoroughly tested; however, they are available for
    export.
