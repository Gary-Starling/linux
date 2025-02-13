exec2: prog
	gcc -o $@ exec2.c

prog: prog.c
	gcc -o $@ $^

clean:
	rm -f prog exec2