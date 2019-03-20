#!/bin/bash

dirs=`ls --hide=LAssert`

fail=0
for d in ${dirs}; do
    if [ -d "${d}" ]; then
        cd $1
        make
        ../run.sh
        fail=$?
        cd ..
    fi
    if [ "${fail}" != "0" ]; then
        break
    fi
done
