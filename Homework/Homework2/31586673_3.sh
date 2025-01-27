#!/bin/bash

if [ ! $1 ]
	then echo "No directory was provided"
	exit 10
fi

traversal () {
	for i in $1/*
		do if [ -d $i ]
			#then echo "DIRECTORY"
			then traversal "$i" "$2"
		elif [ -f $i ]
			#then echo "FILE"
			then grep -P '^[a-zA-Z0-9._-]+@[a-zA-Z]+\.[a-zA-Z]{2,}$' ${i} >> "$2/unique_emails.txt"
		fi
	done
}

x=`pwd`
if [ -f unique_emails.txt ]
	then traversal "$1" "$x"
else
	touch unique_emails.txt
	traversal "$1" "$x"
fi

sort -u unique_emails.txt -o unique_emails.txt
