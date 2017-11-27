#!/bin/makefile

SRC=$(wildcard *.c)
OFILES=$(SRC:.c=.o)
LDFLAGS=-shared -fPIC
CFLAGS=-Wall -Wextra -pedantic -fPIC
EXEC=libSANDAL2.so
CC=gcc


all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $(LDFLAGS) $^ -o $(EXEC)
	mv $(EXEC) sandal2/usr/lib
	cp *.h sandal2/usr/include/SANDAL2

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clear:
	rm *.o

package:
	dpkg-deb --build sandal2

clean: clear

cleaner:
	rm *.o $(EXEC)

install:
	dpkg -i sandal2.deb

uninstall:
	dpkg --purge sandal2
