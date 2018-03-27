project=hello
objects=hello.o file_io.o page.o editing.o
links=ncurses
cc=gcc
cflags=-g -std=c99 -Wall
file=text.txt

exec: $(project)
	./$< $(file)

all: $(objects)

$(project): $(objects)
	$(cc) -o $(project) $(objects) -l$(links)

$(objects): %.o: %.c
	$(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -f $(project) *.out *.o *.log *.txt
