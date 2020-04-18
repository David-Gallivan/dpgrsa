#JMJ

EFLAGS = gcc -g -Wall -O0     # to compile executables
OFLAGS = gcc -g -Wall -O0 -c  # to compile objects
LDLIBS = -lgmp

fermatprimality.o:
	$(OFLAGS) math/fermatprimality.h -o obj/fermatprimality.o $(LDLIBS)

blumblumshub.o:
	$(OFLAGS) math/blumblumshub.h -o obj/blumblumshub.o $(LDLIBS)

largeinteger.o:
	$(OFLAGS) math/largeinteger.h -o obj/largeinteger.o $(LDLIBS)

randomprime.o:
	$(OFLAGS) math/randomprime.h -o obj/randomprime.o $(LDLIBS)

#test: largeinteger.o blumblumshub.o
test:
	$(EFLAGS) test.c -o bin/test $(LDLIBS)
	./bin/test

clean:
	rm bin/* obj/*
