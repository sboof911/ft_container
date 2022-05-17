#!/bin/sh

#to run the scipt :   sh push.sh Path TimeToSleep
while true
do
    cp $1/* .
    git add *
    git commit -m "all good"
    git push
    sleep $2
done