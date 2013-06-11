#!/bin/bash

isLinux=0
[ -x /proc ] && isLinux=1

if [ ${isLinux} = 1 ] ; then
    NUMBER_OF_PROCESSORS=`cat /proc/cpuinfo | grep processor | wc -l`
    trash=/dev/null
else
    trash=nul
fi
MAKE_THREADS=$((${NUMBER_OF_PROCESSORS} + 1))

make clean > $trash

echo -e "\n*** Building using ${MAKE_THREADS} threads (explicit -j switch) ***\n"

make -j${MAKE_THREADS}

make clean > $trash

echo -e "\n*** Building using ${MAKE_THREADS} threads (implicit -j switch in MAKEFLAGS) ***\n"

MAKEFLAGS=-j5 make

make clean > $trash

echo -e "\n*** Building using one thread ***\n"

make
