#!/bin/bash

if [ ! $1 ]
        then echo "Please provide a C File"
        read cFile
else
        cFile=$1

fi

if [ -f "scanf_log.txt" ]
	then grep -P -i "scanf" $cFile >> "scanf_log.txt"

else
	touch scanf_log.txt | grep -P -i "scanf" $cFile > "scanf_log.txt"
fi


if [ -f "printf_log.txt" ]
        then grep -P -i "printf" $cFile >> "printf_log.txt"

else
        touch printf_log.txt | grep -P -i "printf" $cFile > "printf_log.txt"
fi

echo -e "Number of lines with scanf:"
sLine=`grep -P -i "scanf" $cFile | wc -l`
echo $sLine

echo -e "\nNumber of lines with printf:"
pLine=`grep -P -i "printf" $cFile | wc -l`
echo $pLine

totLine=`wc -l < $cFile`
echo -e "\nTotal lines in input file: $totLine"

echo -e "\nPercentage of lines containing scanf: $((($sLine*100)/$totLine))%"
echo -e "\nPercentage of lines containing scanf: $((($pLine*100)/$totLine))%"
