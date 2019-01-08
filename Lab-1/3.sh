#!/bin/bash
read n
declare -a fibonacci=(0 1)
for (( i=2; i < n; i++ )); do
	fibonacci[i]=$((fibonacci[i-1] + fibonacci[i-2]))
done
echo -ne The generated fibonacci sequence is: 
echo "${fibonacci[@]}"

sz=$((n/3))
echo -ne Concatenating the first and third segment element wise:  
for (( i = 0; i < sz; i++ )); do
	fibonacci[i]=$((fibonacci[i] + fibonacci[i+2*sz]))
	echo -ne "${fibonacci[i]}"
done
echo
echo -ne Final answer after concatenating: 
for (( i = 0; i < 2*sz; i++ )); do
 	echo -ne "${fibonacci[i]}"
done 