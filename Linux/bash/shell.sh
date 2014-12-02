#!/bin/bash

shopt -s expand_aliases

CompilerOutput=./output
alias nmake=" make 1>> ${CompilerOutput} 2>> ${CompilerOutput}"

nmake install

Default='\033[0m'
Black='\033[30m'
Red='\033[31m'
Green='\033[32m'
Yellow='\033[33m'
Blue='\033[34m'
Magenta='\033[35m'
Cyan='\033[36m'
White='\033[37m'
Bold='\033[1m'
Halftone='\033[2m'
Underline='\033[4m'
Flash='\033[5m'
Test='\033[3m'

echo -e $Underline$Red"Bright Red"$Default
echo -e $Flash$Green"Flash Green"$Default
echo -e $Bold$Blue"Bold Blue"$Default
echo -e $Halftone$Yellow"Halftone Yellow"$Default
echo -e $Test$Magenta"Test Magenta"$Default

ThisScriptName=$(basename ${0})
StartupDirectory=${PWD}
if [ -f ${StartupDirectory}/${ThisScriptName} ] ; then
    echo "Exist!"
else
    echo "Not exist!"
fi
