#!/bin/sh

#to run the scipt :   sh push.sh Path TimeToSleepInMinits 2
declare -i Time=$2
help=$3
if help
then
    echo "IMIN"
    comment=help
else
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