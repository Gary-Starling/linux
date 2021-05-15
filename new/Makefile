all: exe

exe:	hello.h main.c lib
	gcc main.c -ldl -o hello

lib:	hello.h hello.c
	gcc -shared hello.c -o libHello.so

clean:
	-rm hello libHello.so 2>/dev/null
