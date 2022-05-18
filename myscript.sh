#!/bin/sh

#to run the scipt :   sh push.sh Path TimeToSleepInMinits 
declare -i Time=$2
if $3
then
    comment=$3
else
    comment="all good"
fi
Time=Time*60
while true
do
    cp $1/* .
    git add *
    git commit -m comment
    git push

    sleep $Time
done