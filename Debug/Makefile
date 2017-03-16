#!/bin/makefile

#change this variable to match the path from the current directory to where SANDAL2 is store (without the last '/')
SANDAL2PATH=..

#in this part, nothing for you to be done, it is the inclusion of SANDAL2's files and LDFLAGS
#SANDAL2's files
SANDAL2=$(SANDAL2PATH)/SANDAL2.o $(SANDAL2PATH)/WindowSDL2.o $(SANDAL2PATH)/ElementSDL2.o $(SANDAL2PATH)/FontSDL2.o $(SANDAL2PATH)/DisplayCode.o $(SANDAL2PATH)/HitBox.o $(SANDAL2PATH)/Sprite.o
#SANDAL2's LDFLAGS
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lm
#added because .o files are made in your directory
OSANDAL2=SANDAL2.o WindowSDL2.o ElementSDL2.o FontSDL2.o DisplayCode.o HitBox.o Sprite.o

#add to this variables all the '.o' files for your program
OFILES=debug.o

#add the LDFLAGS you need (such as -g or -O)
LDFLAGS+=-g

#your compilation flags, do not put ansi
CFLAGS=-Wall -Wextra -pedantic

#your program's name
EXEC=debug


all:$(EXEC)

$(EXEC):$(OFILES) $(SANDAL2)
	gcc $(OFILES) $(OSANDAL2) -o $(EXEC) $(LDFLAGS) $(DEBUG)

%.o:%.c
	gcc -c $< $(CFLAGS)

clear:
	rm *.o

clean: clear

cleaner:
	rm *.o $(EXEC)
