#!/bin/bash
files=($(ls -lhS $PWD/OS))
declare -a positions=(10 19 28 37)
for (( i = 0; i < 4; i++ )); do
	index="${positions[$i]}"
	file="${files[$index]}"
	line=$(head -n 1 $PWD/OS/$file)
	echo $line >> $PWD/OS/empty.txt
done
