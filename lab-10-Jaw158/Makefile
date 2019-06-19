all: mult.o
	gcc mult.o -o mult

mult.o: ./csv/multiplier.c
	gcc -c ./csv/multiplier.c -o mult.o

clean:
	rm -rf *.o
	rm mult
