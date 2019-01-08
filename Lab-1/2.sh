#! /bin/bash

# The number of unique words.
grep -o -E '\w+' welcome.txt | tr ' ' '\n' | sort -u | wc -l

# Finding the most frequent word.
cat welcome.txt | tr ' ' '\n' | sort | uniq -c | sort -nr | head -1