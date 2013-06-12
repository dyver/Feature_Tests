#!/bin/bash

. ./defs.sh

if [ $isLinux = 1 ] ; then
    export LD_LIBRARY_PATH=$compiler_lib_path
    ./bin/cpp11.elf
else
    ./bin/cpp11.exe
fi
