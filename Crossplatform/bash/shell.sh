#!/bin/bash

shopt -s expand_aliases

compiler_output=./output
alias nmake=" make 1>> ${compiler_output} 2>> ${compiler_output}"

nmake install

default='\E[0m'
black='\E[30m'
red='\E[31m'
green='\E[32m'
yellow='\E[33m'
blue='\E[34m'
magenta='\E[35m'
cyan='\E[36m'
white='\E[37m'
bold='\E[1m'
halftone='\E[2m'
underline='\E[4m'
flash='\E[5m'
test='\E[3m'


echo -e $underline$red"Bright red"$default
echo -e $flash$green"Flash green"$default
echo -e $bold$blue"Bold blue"$default
echo -e $halftone$yellow"Halftone yellow"$default
echo -e $test$magenta"Test magenta"$default

THIS_SCRIPT_NAME=`basename ${0}`
STARTUP_DIR=$PWD
if [ -f $STARTUP_DIR/$THIS_SCRIPT_NAME ] ; then
    echo "Exist!"
else
    echo "Not exist!"
fi
