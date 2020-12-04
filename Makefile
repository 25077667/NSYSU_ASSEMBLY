CC=gcc
FLAG=-std=gnu99 -Og -Wall -g
OBJ=eea.o poly.o e4c_lite.o ntru.o

all: dep test
	@echo "done"

test: dep 
	$(CC) $(FLAG) driver/testPoly.c $(OBJ) -o poly.elf
	$(CC) $(FLAG) driver/testNTRU.c $(OBJ) -o ntru.elf

dep:
	$(CC) $(FLAG) -c lib/eea.c
	$(CC) $(FLAG) -c lib/poly.c
	$(CC) $(FLAG) -c lib/e4c_lite.c
	$(CC) $(FLAG) -c lib/ntru.c

clean:
	rm -rf *.o *.elf