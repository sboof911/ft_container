#!/bin/sh

#to run the scipt :   sh push.sh Path TimeToSleepInMinits 2
declare -i Time=$2
declare var=$3
if [ -z "$1"]
then
    echo "                      $(tput setaf 3) THIS SCRIPT PUSH UR FOLDER TO UR GIT"
    echo "$(tput setaf 1)use this command : sh myscript.sh $(tput setaf 6)[PATH OF DIRECTORY] [TIME TO SLEEP WITH MIN] [COMMENT](optionnel)"
    exitƒ
elif [ -n "$var" ]
then
    comment=$var
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

    declare i=0
    while [i < 10]
    do
        declare j=$Time-i*$Time
        echo "$(tput setaf 3)Waking up in $j"
        sleep $Time/10
        i++
    done
done