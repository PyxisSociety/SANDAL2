#!/bin/bash

cd tests 2> /dev/null

dirs=`ls --hide=LAssert`

for d in $dirs; do
    if [ -d "$d" ]; then
	cd $d
	if [ -f "Makefile" ]; then
	    make > /dev/null
	    echo "build: $d"
	fi
	cd ..
    fi
done
