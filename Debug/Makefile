#!/bin/makefile

SDL2TK=../SANDAL2.o ../WindowSDL2.o ../ElementSDL2.o ../FontSDL2.o ../DisplayCode.o ../HitBox.o ../Sprite.o
SDL2TKFLAG=-lSDL2 -lSDL2_ttf -lSDL2_image -lm
OFILE=debug.o
OFLAG=-Wall -ansi -Wextra -pedantic
CFLAG=
PROG=debug
DEBUG=-g

$(PROG):$(SDL2TK) $(OFILE)
	gcc $(SDL2TK) $(OFILE) -o $(PROG) $(OFLAG) $(DEBUG) $(SDL2TKFLAG)
	rm ../*.o


.o:.c
	gcc -c $< $(CFLAG)

clear:
	rm *.o *~
