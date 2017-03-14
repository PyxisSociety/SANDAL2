#!/bin/makefile

SANDAL2PATH=SANDAL2

SANDAL2=$(SANDAL2PATH)/SANDAL2.o $(SANDAL2PATH)/WindowSDL2.o $(SANDAL2PATH)/ElementSDL2.o $(SANDAL2PATH)/FontSDL2.o $(SANDAL2PATH)/DisplayCode.o $(SANDAL2PATH)/HitBox.o
SANDAL2FLAG=-lSDL2 -lSDL2_ttf -lSDL2_image -lm
OFILESANDAL2=SANDAL2.o WindowSDL2.o ElementSDL2.o FontSDL2.o DisplayCode.o HitBox.o


OFILE=main.o menu.o jeu.o $(OFILESANDAL2)
OFLAG=
CFLAG=-Wall  -Wextra -pedantic
PROG=jumper
DEBUG=-g

$(PROG):$(SANDAL2) $(OFILE)
	gcc $(OFILE) -o $(PROG) $(OFLAG) $(DEBUG) $(SANDAL2FLAG)

%.o:%.c
	gcc -c $< $(CFLAG)

clear:
	rm *.o *~
