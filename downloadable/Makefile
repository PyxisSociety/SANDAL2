#!/bin/makefile

# ------------------ USER SECTION -------------------
# In this section, you have things to add

# change this variable to match the path from the current directory to where SANDAL2 is store without the last '/'
SANDAL2PATH=

# add the LDFLAGS you need (such as -g or -O), lm and SDL2 flags for SDL2, SDL2_image and SDL2_ttf are already added 
# -ansi or -std=gnu89 is not compatible with lm on gcc
LDFLAGS=-g

#your compilation flags, 
#-ansi or -std=gnu89 are not compatible with -lm on gcc
CFLAGS=-Wall -Wextra -pedantic

#your program's name
EXEC=a.out

#your compiler
CC=gcc

# add to this variables all the '.c' files for your program 
# $(wildcard *.c) is equivalent to all the .c files in the current folder
SRC=$(wildcard *.c)

# you do not need to touch this variable
OFILES=$(SRC:.c=.o)
# -------------- END OF USER SECTION ----------------



# ------------------ DEV SECTION --------------------
# in this part, nothing for you to be done, it is the inclusion of SANDAL2's files and LDFLAGS
#SANDAL2's files
SANDAL2SRC=$(wildcard $(SANDAL2PATH)/*.c)
SANDAL2=$(SANDAL2SRC:.c=.o)
#SANDAL2's LDFLAGS
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_image -lm
#added because .o files are made in your directory
# -------------- END OF DEV SECTION -----------------

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
