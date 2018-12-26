#!/bin/bash

cd tests 2> /dev/null

dirs=`ls --hide=LAssert`
exeCode=0

for d in $dirs; do
    if [ -d "$d" ]; then
	cd $d
	if [ -f "a.out" ]; then
	    out=`./a.out`
	    failed=0
	    for m in ${out}; do
		if [ "$m" == "Failed" ]; then
		    failed=1
		fi
	    done
	    if [ "${failed}" == "1" ]; then
		exeCode=1
		echo "=============================================================="
		echo "Failed: $d"
		echo ""
		echo "${out}"
		echo "=============================================================="
	    else
		echo "++++++ $d success"
	    fi
	fi
	cd ..
    fi
done

exit ${exeCode}
