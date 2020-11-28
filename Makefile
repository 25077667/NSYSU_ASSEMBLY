CC := gcc
FLAG := -std=gnu99 -Og -Wall -g
OBJ:=eea.o poly.o

all: dep test
	@echo done

test: dep
	$(CC) $(FLAG) driver/testPoly.c $(OBJ) -o test.elf

dep:
	$(CC) $(FLAG) -c lib/eea.c
	$(CC) $(FLAG) -c lib/poly.c

clean:
	rm -rf *.o *.elf