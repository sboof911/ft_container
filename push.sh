#!/bin/sh

while true
do
    cp $1/* .
    git add *
    git commit -m "all good"
    git push
    sleep $2
done