all: minesweeper

External.o: External.c External.h
	gcc -c External.c -o External.o

main.o: main.c
	gcc -c main.c -o main.o

Map.o: Map.c Map.h
	gcc -c Map.c -o Map.o

minesweeper: External.o main.o Map.o
	gcc External.o main.o Map.o -o minesweeper

clean:
	rm -v *.o minesweeper