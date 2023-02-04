#Make for printup app
PROG_NAME=string_up.o
CC=gcc
CCFLAGS=-Wall -g

#Clean
CLEAN=rm
CLEAN_FLAGS=-f
CLEAN_COMMAND=$(CLEAN) $(CLEAN_FLAGS) 

#Object files
OBJECT_FILES=*.o

#Source files
SOURCE_FILES=string_up.c


#$(PROG_NAME): $(OBJECT_FILES)
#	$(CC) $(CCFLAGS) -o $@ $^

$(PROG_NAME): $(SOURCE_FILES)
	$(CC) $(CCFLAGS) -c $^
#clean
clean:
	$(CLEAN_COMMAND) *.o
#	$(CLEAN_COMMAND) $(PROG_NAME)
