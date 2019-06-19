all: orbit.o
	gcc -lm orbit.o -o orbit

orbit.o: orbit.c
	gcc -lm -c orbit.c -o orbit.o

clean:
	rm -rf *.o
	rm orbit
	rm path.txt
	rm trajectory.png
