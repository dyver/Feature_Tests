#!/bin/python

import os
import sys
import shutil

def rm(path):
    if os.path.isfile(path):
        os.remove(path)
        return()
    if os.path.isdir(path):
        shutil.rmtree(path)
        return()

Name = 'any-cast'
Flags = '-std=c++11 -Wall -Wextra -Werror -pedantic'
Objects = 'main.cpp'

if len(sys.argv) > 1 and sys.argv[1] == 'Clean':
    rm('any-cast')
    rm('any-cast.exe')
else:
    os.system('g++' + ' ' + Flags + ' ' + '-o' + ' ' + Name + ' ' + Objects)
