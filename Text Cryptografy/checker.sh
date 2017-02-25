#!/bin/bash

mkdir output
make
TOTAL=0;

if [ $# == 0 ]
then 
	startTest=1
	finalTest=10
elif [ "$1" == "all" ]
then
	startTest=1
	finalTest=10
elif [ $1 -ge 1 ] && [ $1 -le 10 ]
then
	startTest=$1
	finalTest=$1
else
	echo -e "\nTest $1 don't exist!\n"
	exit 0
fi

for ((i=$startTest;i<=$finalTest;i++))
do
	input="input"$i
	output="output"$i
	ref="ref"$i

	./tema2 < "input/$input" > "output/$output"

	output1=$(cat "output/$output" | head -n 1)
	output2=$(cat "output/$output" | head -n 2 | tail -n 1)
	output3=$(cat "output/$output" | tail -n 1)

	ref1=$(cat "ref/$ref" | head -n 1)
	ref2=$(cat "ref/$ref" | head -n 2 | tail -n 1)
	ref3=$(cat "ref/$ref" | tail -n 1)

	echo "TEST $i:"
	if [ "$output1" == "$ref1" ] 
	then
		TOTAL=$((TOTAL+2))
		echo "	Task 1: OK!"
	else
		echo "	Task 1: WRONG!"
	fi

	if [ "$output2" == "$ref2" ]
	then
		TOTAL=$((TOTAL+3))
		echo "	Task 2: OK!"
	else
		echo "	Task 2: WRONG!"
	fi

	if [ "$output3" == "$ref3" ]
	then
		TOTAL=$((TOTAL+3))
		echo "	Task 3: OK!"
	else
		echo "	Task 3: WRONG!"
	fi

done

if [ $TOTAL == 80 ] 
then
	echo -e "\nTOTAL: $TOTAL points (MAXIMUM!)\n"
else 
	echo -e "\nTOTAL: $TOTAL points\n"
fi

make clean	
rm -rf output
