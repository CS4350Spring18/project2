objs=project2.o
project=project2
links=ncurses

exec: hello
	./$<

hello: hello.c editing.h page.h
	gcc -g -std=c99 -o hello $< -l$(links)

.PHONY: clean
clean:
	rm -f hello *.out *.o
