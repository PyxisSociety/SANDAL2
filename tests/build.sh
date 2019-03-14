#!/bin/bash

cd tests 2> /dev/null

mkdir -p build
cd build
cmake ..
make
