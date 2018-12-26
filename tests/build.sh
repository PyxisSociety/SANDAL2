#!/bin/bash

cd tests 2> /dev/null

dirs=`ls --hide=LAssert`

for d in $dirs; do
    if [ -d "$d" ]; then
	cd $d
	make cleaner > /dev/null
	make > /dev/null
	cd ..
    fi
done
