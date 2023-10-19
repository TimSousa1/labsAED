# AED, last modified abl 2020.10.21
#
# To compile progs:
#    make   OR  make sorwords
#
# NOTE:
# In case of trouble with the shell for loop, GNU Make has 'foreach':
#	$(foreach file,$(FILES),./labconn $(file);)
# https://stackoverflow.com/questions/1490949/how-to-write-loop-in-a-makefile
#----------------------------------------------------------------------
#   Compiler, Compiler Flags

CC = gcc
CFLAGS = -DDEBUG -g -Wall --std=c99

#   Sources
SOURCES = queens.c stack.c board.c dfs.c

#   Objects  ('make' automatically compiles .c to .o)
OBJECTS = dfs.o stack.o queens.o board.o

queens: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

stack.o: stack.c stack.h

queens.o: queens.c

dfs.o: dfs.c dfs.h
	$(CC) $(CFLAGS) -c -o $@ dfs.c

board.o: board.c board.h




clean:
	rm -f *.o  queens


FILES = $(shell ls ../test/*.txt)

VALG = valgrind --leak-check=full


