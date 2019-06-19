all: gauss-jordan gauss-seidel

gauss-jordan: gauss_jordan.c
	gcc -o gauss-jordan gauss_jordan.c

gauss-seidel: siedel.c
	gcc -o gauss-seidel siedel.c

clean:
	rm -rf *.o
	rm gauss-jordan
	rm gauss-seidel
