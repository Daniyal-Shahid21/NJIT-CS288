#!/bin/bash

if [ -z $1 ]
	then echo "Please enter the name of your directory/file: "
	read userDF
else
	userDF=$1
fi


if [ -d $userDF ]
	then echo "It's a directory"

	if [ -w $userDF ] || [ -r $userDF ]
		then count=$(ls -1A $1 | wc -l)
		echo "Total subdirectories and files: $count"
		echo "List and sizes of subdirectories and files: "
		ls -lh $userDF
	else
		echo "USER IS MISSING READ AND WRITE PERMISSIONS"
	fi


elif [ -f $userDF ]
	then echo "It's a file"
	if [ -r $userDF ]
		then wordCount=$(wc -w < "$userDF")
        	lineCount=$(wc -l < "$userDF")
        	charCount=$(wc -m < "$userDF")

	        echo "Word count: $wordCount"
        	echo "Line count: $lineCount"
        	echo "Char count: $charCount"

        	if [ "$charCount" -gt 10000 ]
			then echo "Text Heavy"
        	elif [ "$charCount" -ge 1000 ]
			then echo "Moderately Sized"
        	else
			echo "Light File"
        	fi
	else
		echo "USER IS MISSING READ PERMISSIONS"
	fi
fi
