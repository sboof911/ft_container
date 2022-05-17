#!/bin/sh

#to run the scipt :   sh push.sh Path TimeToSleepInMinits
declare -i Time=$2
Time=Time*60
echo $Time
while true
do
    cp $1/* .
    git add *
    git commit -m "all good"
    git push

    sleep Time
done