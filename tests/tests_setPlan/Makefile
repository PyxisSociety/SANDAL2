#!/bin/makefile

#change this variable to match the path from the current directory to where SANDAL2 is store 
#without the last '/'
SANDAL2PATH=../..

#in this part, nothing for you to be done, it is the inclusion of SANDAL2's files and LDFLAGS
#SANDAL2's files
SANDAL2SRC=$(wildcard $(SANDAL2PATH)/*.c)
SANDAL2=$(SANDAL2SRC:.c=.o)
#SANDAL2's LDFLAGS
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lm
#added because .o files are made in your directory

#add to this variables all the '.c' files for your program 
#$(wildcard *.c) is equivalent to all the .c files in the current folder
SRC=$(wildcard *.c)
OFILES=$(SRC:.c=.o)

#add the LDFLAGS you need (such as -g or -O), lm already added 
#-ansi or -std=gnu89 is not compatible with lm on gcc
LDFLAGS+=

#your compilation flags, 
#-ansi or -std=gnu89 are not compatible with -lm on gcc
CFLAGS=-Wall -Wextra -pedantic -g

#your program's name
EXEC=a.out

#your compiler
CC=gcc


all:$(EXEC)

$(EXEC):$(OFILES) $(SANDAL2)
	$(CC) $^ -o $(EXEC) $(LDFLAGS) $(DEBUG)

$(SANDAL2PATH)/%.o:$(SANDAL2PATH)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clear:
	rm *.o

clean: clear

cleaner:
	rm *.o $(EXEC)
