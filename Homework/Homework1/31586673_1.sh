#!/bin/bash

declare -A userOpt

userOpt["rock"]=0
userOpt["paper"]=1
userOpt["scissors"]=2

compOpt=("rock" "paper" "scissors")

echo -e "Hello player, welcome to rock, paper, scissors. \nThere are three rules to rock, paper, scissors. \n   Rock beats scissors (by crushing them) \n   Scissors beat paper (by cutting it) \n   Paper beats rock (by covering it)"
tie=1

while [ $tie -eq 1 ]
do
echo "Lets begin! Enter your selection: "
read urps

compNum=$(( (RANDOM % 3) ))
userNum=${userOpt[$urps]}


echo -e "You chose: $urps \nI chose: ${compOpt[compNum]}"


if [ $userNum -eq $compNum ]
then echo "We tied, lets run it back"
fi


if [ $((($userNum + 1) % 3)) -eq $compNum ]
then echo "I win!"
tie=0
fi

if [ $((($compNum + 1) % 3)) -eq $userNum ]
then echo "You win :("
tie=0
fi

done
