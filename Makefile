#!/bin/makefile

SRC=$(wildcard *.c)
OFILES=$(SRC:.c=.o)
LDFLAGS=-shared -fPIC
CFLAGS=-Wall -Wextra -pedantic -fPIC -O2
EXEC=libSANDAL2.so
CC=gcc


all:$(EXEC)

$(EXEC):$(OFILES)
	$(CC) $(LDFLAGS) $^ -o $(EXEC)
	mv $(EXEC) sandal2/usr/lib
	cp *.h sandal2/usr/include/SANDAL2
	cp Doxdoc/Doc/man/man3/*.gz sandal2/usr/share/man/man3

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clear:
	rm *.o

package:
	dpkg-deb --build sandal2
	mv sandal2.deb downloadable

man:
	(cd Doxdoc/Doc/man/man3; gzip *.3$ )

clean: clear

cleaner:
	rm *.o $(EXEC)

install:
	dpkg -i downloadable/sandal2.deb

uninstall:
	dpkg --purge sandal2
