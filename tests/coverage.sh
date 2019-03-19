#!/bin/bash

dirs=`ls --hide=LAssert`

totalPercent=0
totalNbLines=0

for d in ${dirs}; do
    if [ -d "${d}" ]; then
        echo ""
        echo "${d}"
        coverage=`cat ${d}/cov.txt`
        while read -r m; do
	    nbLines=""
	    for l in $m; do
		nbLines=$l
	    done
	    if [[ $m =~ :(.+)% ]]; then
		percent=${BASH_REMATCH[0]:1:-1}
		percent=`bc -l <<< ${percent}*${nbLines}`
		totalPercent=`bc -l <<< ${totalPercent}+${percent}`
		totalNbLines=`expr ${totalNbLines} + ${nbLines}`
		echo "$m"
	    fi
	done <<< "$coverage"
    fi
done

if [[ "$totalNbLines" =~ [0-9]+ ]]; then
    totalPercent=`bc -l <<< ${totalPercent}/${totalNbLines}`
    totalPercent=`bc -l <<< ${totalPercent}*100`
    totalPercent=${totalPercent/.*}
    totalPercent=`bc -l <<< ${totalPercent}/100`
    echo "coverage: ${totalPercent}%"
fi
