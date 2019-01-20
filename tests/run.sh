#!/bin/bash

cd tests 2> /dev/null

dirs=`ls --hide=LAssert`
exeCode=0

totalPercent=0

for d in $dirs; do
    if [ -d "$d" ]; then
	cd $d
	if [ -f "a.out" ]; then
	    out=`./a.out`
	    failed=0
	    for m in ${out}; do
		if [ "$m" == "Failed" ]; then
		    failed=1
		    break
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

	    coverage=`gcov ../../${d}.c -m`
	    while read -r m; do
		nbLines=""
		for l in $m; do
		    nbLines=$l
		done
		if [[ $m =~ :(.+)% ]]; then
		    percent=${BASH_REMATCH[0]:1:-1}
		    percent=`bc -l <<< ${percent}*${nbLines}`
		    totalPercent=`bc -l <<< ${totalPercent}+${percent}`
		    echo "$m - $percent - $nbLines - $totalPercent"
		fi
	    done <<< "$coverage"
	fi
	cd ..
    fi
done

totalNbLines=`cat ../*.c | wc -l`

if [[ "$totalNbLines" =~ [0-9]+ ]]; then
    totalPercent=`bc -l <<< ${totalPercent}/${totalNbLines}`
    echo "coverage: ${totalPercent}%" > coverage.txt
fi

exit ${exeCode}
