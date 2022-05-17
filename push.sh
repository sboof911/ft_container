#!/bin/sh

while true
do
    cp ../ft_container/* .
    git add *
    git commit -m "all good"
    git push
    sleep 10m
done