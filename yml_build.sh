#!/bin/bash

template_file="gitlab-ci.yml.template"
final_file=".gitlab-ci.yml"

if [ -f "${template_file}" ]; then
    content=`cat ${template_file}`
    rm -f ${final_file}
    touch ${final_file}

    # init list of entities
    entity_file="tmp.txt"
    ls_res=`ls src/ > ${entity_file}.tmp`
    touch ${entity_file}
    for name in `cat ${entity_file}.tmp`; do
        echo `echo "${name}" | cut -d'.' -f 1` >> ${entity_file}
    done
    rm -f ${entity_file}.tmp


    
    # parsing template file and generating new file
    isInBlock=0
    block=""
    IFS=$'\n'
    while read -r line; do
        if [ "$line" == "BEGIN" ]; then
            isInBlock=1
        elif [ "$line" == "END" ]; then
            isInBlock=0
            for entity in `cat ${entity_file}`; do
                for bl in "${block}"; do
                    echo -e "${bl//@ENTITY@/$entity}" >> ${final_file}
                done
                echo "" >> ${final_file}
            done
            block=""
        elif [ "$isInBlock" == "1" ]; then
            block="${block}\n${line}"
        elif [[ "${line}" =~ ENTITY_LIST(.*) ]]; then
            p1=`echo "${line}" | cut -d'(' -f 1`
            p1="${p1//ENTITY_LIST/}"
            p2=`echo "${line}" | cut -d'(' -f 2`
            parameter=`echo "${p2}" | cut -d')' -f 1`
            p2=`echo "${p2}" | cut -d')' -f 2`
            result=""
            for entity in `cat ${entity_file}`; do
                result="${p1}${parameter//@ENTITY@/$entity}${p2}\n${result}"
            done
            echo -e "${result}" >> ${final_file}
        else
            echo "${line}" >> ${final_file}
        fi
    done <<< "${content}"

    rm -f ${entity_file}
else
    echo "ERROR: ${template_file} not found"
fi
