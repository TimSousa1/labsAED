#
#  File name: makefile
#
#  Author: 2023/2024 P1, Fall Semester AED Team
#
#  Release date: 2023/09/20
#
#  Description: Makefile for the individual evaluation laboratory
#
#  Usage:
#     1) To generate the executable file for the program p2-pub, run
#         $ make p2
#
#     2) To clean all object files and the executable file, run
#         $ make clean
#

#  Compiler
CC = gcc

#  Compiler Flags
CFLAGS = -g -Wall -ansi -pedantic

#  Sources
SOURCES =  memmgt.c p2-pub.c

#  Objects
OBJECTS = memmgt.o p2-pub.o

p2:	p2-pub
p2-pub: $(OBJECTS)
	gcc -g -o $@ $(OBJECTS)

memmgt.o: memmgt.h memmgt.c
p2-pub.o: memmgt.h p2-pub.c

clean::
	rm -f *.o core a.out p2-pub *~

depend::
	makedepend $(SOURCES)
# DO NOT DELETE
