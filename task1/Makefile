LIBS = -lncurses
CFLAGS = -O3 -Wall

exec: foo
	./foo

foo: foo.o
	gcc $(CFLAGS) -o $@ foo.o $(LIBS)

foo.o: foo.c
	gcc -g $(CFLAGS) -c foo.c

