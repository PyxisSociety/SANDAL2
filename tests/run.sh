#!/bin/bash

exeCode=0

OUTPUT=`make run`
failed=$?

if [ "${failed}" != "0" ]; then
    echo "Failed: $d"
    echo "    failed with code ${failed}"
    echo "    ouput log:"
    echo "${out}"
    exeCode=1
else
    for m in ${out}; do
	if [ "$m" == "Failed" ]; then
	    failed=1
	    break
	fi
    done
    if [ "${failed}" == "1" ]; then
	exeCode=1
	echo "Failed: $d"
	echo ""
	echo "${out}"
    fi
fi

if [ "${exeCode}" == "0" ]; then
    make cov > cov.txt
fi

exit ${exeCode}
