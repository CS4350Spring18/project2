project=foo
objects=foo.o save_file.o load_file.o editing.o page_ops.o find.o newline.o deleteline.o copypaste.o
links=-lncurses
cc=gcc
cflags=-Wall -std=c99 -g -pedantic
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
