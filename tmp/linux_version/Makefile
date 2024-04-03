CC=gcc
CCFLAGS=-Wall -g
MAKE=make
CLEAN=rm -f
PROG_NAME=linux_version
OBJECTS=./version/reader.o ./string_to_up/string_up.o

$(PROG_NAME): make-version make-string_to_up linux_version.o
	$(CC) $(CCFLAGS) -o $(PROG_NAME) $(OBJECTS) linux_version.o

linux_version.o: linux_version.c
	$(CC) $(CCFLAGS) -c -Iversion -Istring_to_up $^

make-version:
	$(MAKE) -C version reader.o

make-string_to_up:
	$(MAKE) -C string_to_up string_up.o

clean:
	$(CLEAN) *.o $(PROG_NAME)
	$(MAKE) -C version clean
	$(MAKE) -C string_to_up clean