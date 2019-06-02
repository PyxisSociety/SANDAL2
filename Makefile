#!/bin/makefile

SRC=$(wildcard *.c)
OFILES=$(SRC:.c=.o)
LDFLAGS=-shared -fPIC
CFLAGS=-Wall -Wextra -pedantic -fPIC -O2
EXEC=libSANDAL2.so
CC=gcc
BUILD_TYPE?=Release


all: doc man
	@rm -rf build
	@mkdir build
	@cd build && cmake -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) .. 
	@cd build && make --no-print-directory
	@cp build/lib* sandal2/usr/lib
	@cp headers/*.h sandal2/usr/include/SANDAL2
	@cp docs/man/man3/*.gz sandal2/usr/share/man/man3
	@echo "\033[0;33mThe installation needs sudo rights, CTRL+C to cancel installation\033[0m"
	@cd build && sudo make install --no-print-directory

clear:
	rm -rf build

clean: clear

package:
	dpkg-deb --build sandal2
	mv sandal2.deb downloadable

man:
	(cd docs/man/man3; gzip -f *.3$ )

doc:
	rm -rf docs/*
	cp downloadable/pixel.png docs
	doxygen Doxyfile
	rm -rf docs/latex
	mv docs/html/* docs
	rmdir docs/html

install:
	dpkg -i downloadable/sandal2.deb

uninstall:
	dpkg --purge sandal2
