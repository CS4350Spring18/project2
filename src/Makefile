objs=hello.o file_io.o page.o editing.o
headers=file_io.h page.h editing.h
project=hello
links=ncurses

exec: $(project)
	./$<

$(project): $(objs)
	gcc -std=c99 -o $(project) $(objs) -l$(links)

hello.o: hello.c 
	gcc -g -c -Wall $<

file_io.o: file_io.c
	gcc -g -c -Wall $<

page.o: page.c
	gcc -g -c -Wall $<

editing.o: editing.c
	gcc -g -c -Wall $<

.PHONY: clean
clean:
	rm -f $(project) *.out *.o
