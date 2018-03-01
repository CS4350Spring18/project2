objs=project2.o
project=project2
links=ncurses

exec: $(project)
	./$<

$(project): $(objs)
	gcc -o $(project) $< -l$(links)

$(objs): project2.c
	gcc -g -c $< -O0 -Wall

.PHONY: clean
clean:
	rm -f $(project).o $(project) *.out
