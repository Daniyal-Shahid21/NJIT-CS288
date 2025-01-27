#!/bin/bash

date=`date +%Y%m%d`

if [ $# -eq 0 ]
	then echo "NO FILES WERE PROVIDED"
	exit 10
elif [ $# -ge 3 ]
	then mkdir "backup_$date"
	touch "backup_$date/logfile.txt"
	for i in $@
		do if [ -f $i ]
			then echo "ARG IS A FILE"
			cp $i "backup_$date/${i%.*}_$date.${i##*.}"
			echo "$i -----> ${i%.*}_$date.${i##*.}" >> "backup_$date/logfile.txt"
		else
			echo "WARNING: This argument is not a file"
		fi
	done
	echo "Backups saved"

else
	echo "Not enough arguments provided"
fi

