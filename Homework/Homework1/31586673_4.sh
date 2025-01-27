#!/bin/bash

subdirSearch() {
	dir=$1
	currTime=`date +%s`
	hist=$((currTime - 86400))

	for i in $dir/*
		do if [ -d $i ]
			then subdirSearch $i

		elif [ -f $i ]
			then modDate=`stat -c %Y $i`
			if [ $modDate -ge $hist ]
				then echo $i
			fi
		fi
	done
}



echo "Please provide a directory name: "
read userDir

if [ -d $userDir ]
	then cd $userDir
else
	echo "Directory does not exist. Would you like to create it: (yes/no)"
	read userInp

	if [ $userInp = "yes" ]
		then mkdir "$userDir"
		cd "$userDir"
	else
		echo "Good bye"
		exit 10
	fi
fi

while true
	do echo -e "\nCurrent dir: `pwd`"
	echo "Files and subdirs:"

	select i in $(ls -1) "Exit"
		do if [ $i = "Exit" ]
			then echo "Good bye"
			exit 10

		elif [ -f $i ]
			then lines=0
			while true
				do head -n $((lines + 10)) $i | tail -n 10
				lines=$((lines + 10))

				if [ $lines -ge `wc -l < $i` ]
					then echo "End of file has been reached"
					break
				fi
				echo "Would you like to display more: (yes/no)"
				read moreDisp
				if [ $moreDisp != "yes" ]
					then break
				fi
			done

		elif [ -d $i ]
			then cd $i
			echo "Files modified in the last 24 hours: "
			recFiles=(`subdirSearch "."`)

			if [ ${#recFiles[@]} -eq 0 ]
				then echo "No files modified in the last 24 hours."
			else
				select recFile in "${recFiles[@]}"
					do if [ -n $recFile ]
						then lines=0
						while true
							do head -n $((lines + 10)) $recFile | tail -n 10
							lines=$((lines + 10))
							if [ $lines -ge `wc -l < $recFile` ]
								then echo "End of file reached"
								break
							fi
							echo "Display more: (yes/no)"
							read moreDisp
							if [ $moreDisp != "yes" ]
								then break
							fi
						done
					fi
					break
				done
			fi
			cd ..
		else
			echo "Invalid selection. Please try again."
		fi
		break
	done
done
