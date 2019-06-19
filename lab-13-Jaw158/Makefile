all: kirchhoff_solve.o
	gcc kirchhoff_solve.o -o kirchhoff_solve

kirchhoff_solve.o: circuit_solver.c
	gcc -c circuit_solver.c -o kirchhoff_solve.o

clean:
	rm -rf *.o
	rm kirchhoff_solve
