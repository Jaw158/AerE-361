CFlags=-I./include -L./lib -lcsv -shared -c

all: ./bin/csvfix.so ./bin/csvinfo.so ./bin/csvtest.so ./bin/csvvalid.so ./bin/csvwriter.so

./bin/csvfix.so: ./tools/csvfix.c ./include/csv.h
	gcc $(CFlags) ./tools/csvfix.c -o ./bin/csvfix.so

./bin/csvinfo.so: ./tools/csvinfo.c ./include/csv.h
	gcc $(CFlags) ./tools/csvinfo.c -o ./bin/csvinfo.so

./bin/csvtest.so: ./tools/csvtest.c ./include/csv.h
	gcc $(CFlags) ./tools/csvtest.c -o ./bin/csvtest.so

./bin/csvvalid.so: ./tools/csvvalid.c ./include/csv.h
	gcc $(CFlags) ./tools/csvvalid.c -o ./bin/csvvalid.so

./bin/csvwriter.so: ./src/csvwriter.c ./include/csv.h
	gcc $(CFlags) ./src/csvwriter.c -o ./bin/csvwriter.so

clean: 
	rm -rf *.o
	rm ./bin/csvfix.so
	rm ./bin/csvinfo.so
	rm ./bin/csvtest.so
	rm ./bin/csvvalid.so
	rm ./bin/csvwriter.so
