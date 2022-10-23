# Makefile
# Řešení IJC-DU1, příklad a), 22.3.2022
# Autor: Jakub Kontrík, FIT
# Přeloženo: gcc 11.2
# Makefile
CC = gcc
CFLAGS = -g -O2 -std=c11 -pedantic -Wall -Wextra
LDLIBS = -lm

.PHONY: clean all run zip

all: primes primes-i steg-decode

run: all
	ulimit -s 40000 && ./primes
	ulimit -s 40000 && ./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $^ -o primes $(LDLIBS)

primes.o: primes.c bitset.h error.h eratosthenes.h

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h error.h

error.o: error.c error.h

primes-i: primes-i.o eratosthenes-i.o error-i.o bitset-i.o
	$(CC) $^ -o primes-i $(LDLIBS)

primes-i.o: primes.c bitset.h error.h eratosthenes.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c $< -o $@

eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h error.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c $< -o $@

error-i.o: error.c error.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c $< -o $@

bitset-i.o: bitset.c bitset.h error.h
	$(CC) -DUSE_INLINE $(CFLAGS) -c $< -o $@


steg-decode: steg-decode.o ppm.o error.o eratosthenes.o
	$(CC) $^ -o steg-decode $(LDLIBS)

steg-decode.o: steg-decode.c bitset.h error.h eratosthenes.h ppm.h

ppm.o: ppm.c ppm.h error.h bitset.h


zip:
	zip xkontr02.zip *.c *.h Makefile

clean:
	rm -f *.o steg-decode primes primes-i

