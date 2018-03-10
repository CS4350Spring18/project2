objs=project2.o
project=project2
links=ncurses

hello: hello.c editing.h page.h
	gcc -g -std=c99 -o hello hello.c -lncurses

.PHONY: clean
clean:
	rm -f hello *.out *.o
