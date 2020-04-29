#JMJ

EFLAGS = gcc -g -Wall -O0     # to compile executables
OFLAGS = gcc -g -Wall -O0 -c  # to compile objects
LDLIBS = -lgmp

other:
	echo "read the README"

eea.o:
	$(OFLAGS) alg/eea.h -o obj/eea.o $(LDLIBS)

fermatprimality.o:
	$(OFLAGS) alg/fermatprimality.h -o obj/fermatprimality.o $(LDLIBS)

blumblumshub.o:
	$(OFLAGS) alg/blumblumshub.h -o obj/blumblumshub.o $(LDLIBS)

largeinteger.o:
	$(OFLAGS) alg/largeinteger.h -o obj/largeinteger.o $(LDLIBS)

randomprime.o:
	$(OFLAGS) alg/randomprime.h -o obj/randomprime.o $(LDLIBS)

modexp.o:
	$(OFLAGS) alg/modexp.h -o obj/modexp.o $(LDLIBS)

rsa.o:
	$(OFLAGS) alg/modexp.h -o obj/rsa.o $(LDLIBS)

# TODO: have it compile libraries, too
#archive: rsa.o
#	ar rc dpgrsa.a obj/rsa.o
#	ranlib dpgrsa.a

keysetup:
	$(EFLAGS) test/keysetup.c -o bin/keysetup $(LDLIBS)

encrypt:
	$(EFLAGS) test/encrypt.c -o bin/encrypt $(LDLIBS)

decrypt:
	$(EFLAGS) test/decrypt.c -o bin/decrypt $(LDLIBS)

all: keysetup encrypt decrypt eea.o fermatprimality.o \
       blumblumshub.o largeinteger.o randomprime.o modexp.o \
       rsa.o 

run: all
	./run.sh

clean:
	rm bin/* obj/* results/*
