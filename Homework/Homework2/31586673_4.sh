#!/bin/bash

if [ ! $1 ]
	then echo "Please provide a file: "
	read file
else
	file=$1
fi

if [ -f Ages.txt ]
	then rm "Ages.txt"
fi

touch Ages.txt
grep -P '^.+,.+,.+[ ].+,.+' $file | sed -E 's/.*([A-Z].+[[:space:]].*,[[:space:]][0-9]{4}).*/\1/' >> Ages.txt

temp=`mktemp`

while IFS=, read -r name year
	do age=$((2024 - year))
	echo $name, $age >> $temp
done < Ages.txt

mv $temp Ages.txt

sort -t, -k2 -nr "Ages.txt"
rm Ages.txt
