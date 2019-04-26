#
# This is a Makfile to compile the sources of 1st 'devoir'
#

# Compiler
CC=gcc

# GCC flags to avoid stack protection
CCFLAGS=-ggdb -Wall

exe: client.c fonctions.h fonctions.c
	$(CC) -o client client.c fonctions.h fonctions.c $(CCFLAGS)

clean:
	rm t

