#!/bin/bash

isLinux=0
[ -x /proc ] && isLinux=1

if [ $isLinux = 1 ] ; then
    export LD_LIBRARY_PATH=/opt/gcc-4.8.0/lib
    ./bin/cpp11.elf
else
    ./bin/cpp11.exe
fi