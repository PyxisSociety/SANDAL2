#!/bin/makefile
all:
	@make clear --no-print-directory
	@mkdir build
	@cd build && cmake ..
	@cd build && make --no-print-directory

clear:
	rm -rf build

clean: clear
