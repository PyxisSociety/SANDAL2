#!/bin/makefile
SANDAL2_PATH=$(shell (cd ../..; pwd))
CURRENT_PATH=$(shell pwd)
ENTITY=$(shell basename $(CURRENT_PATH))

all:
	@make clear --no-print-directory
	@mkdir build
	@cd build && cmake ..
	@cd build && make --no-print-directory

run:
	@(cd build; ./SANDAL2_test_$(ENTITY))

cov:
	gcov build/CMakeFiles/SANDAL2_test_$(ENTITY).dir$(SANDAL2_PATH)/src/$(ENTITY).c.o

clear:
	@rm -rf build
	@rm -f *.o*
	@rm -f *.gc*

clean: clear
