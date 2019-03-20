#!/bin/bash

dirs=`ls --hide=LAssert`

for d in ${dirs}; do
    if [ -d "${d}" ]; then
        cd ${d}
        make
        ../run.sh
        cd ..
    fi
done
