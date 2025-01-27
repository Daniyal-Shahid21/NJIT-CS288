#!/bin/bash

if [ ! $1 ]
	then echo "Please provide dictionary"
	read dic
else
	dic=$1

fi

echo "Here's the following count of words with at least three a's"
grep -P -i 'a.*a.*a' $dic -c

echo -e "\nHere's the following count of words with exactly three e's seperated by a non-'e' character"
grep -P -i '^[^e]*e[^e]+e[^e]+e[^e]*$' $dic -c

echo -e "\nHere are the following three most common letters found in the last three letters of words whose that contain two adjacent e's"
grep -P -i 'ee' $dic | sed 's/.*\(...$\)/\1/' | sort | uniq -c | sort -n -r| head -n3
