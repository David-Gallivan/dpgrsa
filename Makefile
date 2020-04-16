#JMJ

EFLAGS = gcc -g -Wall -O0     # to compile executables
OFLAGS = gcc -g -Wall -O0 -c  # to compile objects
LDLIBS = -lgmp

blumblumshub.o:
	$(OFLAGS) math/blumblumshub.h -o obj/blumblumshub.o $(LDLIBS)

largeinteger.o: blumblumshub.o
	$(OFLAGS) math/largeinteger.c -o obj/largeinteger.o $(LDLIBS)

#test: largeinteger.o blumblumshub.o
test: blumblumshub.o
	$(EFLAGS) test.c -o bin/test $(LDLIBS)
	./bin/test

clean:
	rm bin/* obj/*
