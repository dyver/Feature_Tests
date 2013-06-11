#!/bin/bash

isLinux=0
[ -x /proc ] && isLinux=1

if [ $isLinux = 1 ] ; then
    trash=/dev/null
else
    trash=nul
fi

echo -n "Cleaning targets "

root_dir=$PWD

find . -type d | (
    while read item ; do
        echo -n .
        cd "$item" &> $trash
        bash ./clean.sh &> $trash
        cd "$root_dir"
    done
)

echo " done"
