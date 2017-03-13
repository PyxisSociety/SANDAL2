#!/bin/makefile

SANDAL2PATH=

SANDAL2=$(SANDAL2PATH)/SANDAL2.o $(SANDAL2PATH)/FenetreSDL2.o $(SANDAL2PATH)/ElementSDL2.o $(SANDAL2PATH)/FontSDL2.o $(SANDAL2PATH)/DisplayCode.o $(SANDAL2PATH)/HitBox.o
SANDAL2FLAG=-lSDL2 -lSDL2_ttf -lSDL2_image -lm

OFILE=
OFLAG=-Wall -ansi -Wextra -pedantic
CFLAG=
PROG=
DEBUG=-g

$(PROG):$(SANDAL2) $(OFILE)
	gcc $(SDL2TK) $(OFILE) -o $(PROG) $(OFLAG) $(DEBUG) $(SANDAL2FLAG)
	rm ../*.o


.o:.c
	gcc -c $< $(CFLAG)

clear:
	rm *.o *~
