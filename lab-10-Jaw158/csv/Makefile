all: mult.o
	gcc mult.o -o mult

mult.o: multiplier.c
	gcc -c multiplier.c -o mult.o

clean:
	rm -rf *.o
	rm mult
