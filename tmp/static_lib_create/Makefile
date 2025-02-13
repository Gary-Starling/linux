libmyenv.a: setenv.o printenv.o
	ar rv $@ $^

setenv.o: setenv.c
	gcc -c $^

printenv.o: printenv.c
	gcc -c $^

clean:
	rm -f libmyenv.a *.o




#$@ — содержит имя текущей цели;
#$^ — содержит список зависимостей в текущей связке