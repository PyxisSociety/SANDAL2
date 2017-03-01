#!/bin/makefile

OFLAG= -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_ttf -g
CFLAG=-Wall -Wextra -pedantic -ansi -g
SDL2TKPATH=../
SDL2TK=$(SDL2TKPATH)FenetreSDL2.o $(SDL2TKPATH)SDL2TK.o $(SDL2TKPATH)ElementSDL2.o $(SDL2TKPATH)DisplayCode.o $(SDL2TKPATH)FontSDL2.o

debug: debug.o $(SDL2TK)
	gcc $? -o $@ $(OFLAG)

.o:.c
	gcc -c $< $(CFLAG)

clean:
	rm *.o *~
clear: clean
