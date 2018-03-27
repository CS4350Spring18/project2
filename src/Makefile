project=hello
objects=hello.o file_io.o page.o editing.o
links=-lncurses
cc=gcc
cflags=-Wall -Werror -std=c99 -g -pedantic
file=text.txt

exec: $(project)
	./$< $(file)

all: $(objects)

$(project): $(objects)
	$(cc) -o $(project) $(objects) $(links)

$(objects): %.o: %.c
	$(cc) -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -f $(project) $(objects) *.out *.log *.txt
