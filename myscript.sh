#!/bin/sh

#to run the scipt :   sh push.sh Path TimeToSleepInMinits 2
declare -i Time=$2
var=$3
if $var
then
    echo "IMIN1"
    comment=$var
else
    echo "IMIN2"
    comment="all_good"
fi
Time=Time*60
while true
do
    cp -rf $1/* .
    git add *
    git commit -m $comment
    git push

    sleep $Time
done