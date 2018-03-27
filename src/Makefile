objs=hello.o file_io.o page.o editing.o
headers=file_io.h page.h editing.h
project=hello
links=ncurses

exec: $(project)
	./$< text.txt

$(project): $(objs)
	gcc -o $(project) $(objs) -l$(links)

hello.o: hello.c 
	gcc -g -c -std=c99 -Wall $<

file_io.o: file_io.c
	gcc -g -c -std=c99 -Wall $<

page.o: page.c
	gcc -g -c -std=c99 -Wall $<

editing.o: editing.c
	gcc -g -c -std=c99 -Wall $<

.PHONY: clean
clean:
	rm -f $(project) *.out *.o *.log *.txt
