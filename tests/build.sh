#!/bin/bash

ls downloadable

cd tests 2> /dev/null

dirs=`ls --hide=LAssert`

for d in $dirs; do
    if [ -d "$d" ]; then
	cd $d
	if [ -f "Makefile" ]; then
	    make cleaner 2> /dev/null
	    make
	    echo "build: $d"
	fi
	cd ..
    fi
done
