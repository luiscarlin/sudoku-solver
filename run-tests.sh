#!/usr/bin/env bash

index=0
failed=0
passed=0

while read -r line || [[ -n "$line" ]]
do
    if ! [[ -z "$line" ]] 
    then
        array[$index]="$line"
        index=$((index+1))
    fi
done < "$1"

index=0


echo
echo Running Tests
echo =============
while [ $index -lt ${#array[@]} ]
do
    echo -n ${array[$index]}
    index=$((index+1))
    
    result=$(./sudoku-solver -i ${array[$index]})
    index=$((index+1))

    if [[ $result == ${array[$index]} ]]
    then
	echo " ==> Passed"
        passed=$((passed+1))
    else
        echo " ==> Failed"
        failed=$((failed+1))
    fi
    index=$((index+1)) 
done
echo
echo Summary
echo =======
echo "Passed = $passed"
echo "Failed = $failed"
echo

