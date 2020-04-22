#JMJ

EFLAGS = gcc -g -Wall -O0     # to compile executables
OFLAGS = gcc -g -Wall -O0 -c  # to compile objects
LDLIBS = -lgmp

other:
	echo "read the README"

eea.o:
	$(OFLAGS) math/eea.h -o obj/eea.o $(LDLIBS)

fermatprimality.o:
	$(OFLAGS) math/fermatprimality.h -o obj/fermatprimality.o $(LDLIBS)

blumblumshub.o:
	$(OFLAGS) math/blumblumshub.h -o obj/blumblumshub.o $(LDLIBS)

largeinteger.o:
	$(OFLAGS) math/largeinteger.h -o obj/largeinteger.o $(LDLIBS)

randomprime.o:
	$(OFLAGS) math/randomprime.h -o obj/randomprime.o $(LDLIBS)

keysetup:
	$(EFLAGS) crypt/keysetup.c -o bin/keysetup $(LDLIBS)

encrypt:
	$(EFLAGS) crypt/encrypt.c -o bin/encrypt $(LDLIBS)

decrypt:
	$(EFLAGS) crypt/decrypt.c -o bin/decrypt $(LDLIBS)

all: keysetup encrypt decrypt

run: all
	./run.sh

clean:
	rm bin/* obj/* testeea/*.exe *.txt
