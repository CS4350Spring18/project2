exec: project2
	./project2

project2: project2.o
	gcc -o project2 project2.o -lncurses

project2.o: project2.c
	gcc -g -c project2.c -O0 -Wall

clean:
	rm -f project2*.o project2 *.out
