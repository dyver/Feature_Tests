#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys

Name1 = 'ordinal'
Name2 = 'optimized'
CommonFlags = '-std=c++98 -Wall -Wextra -Werror -pedantic-errors'
CommonFlags += ' -DDEBUG_LEVEL=0 -DDEBUG_OUT_DESTINATION=1 -DDEBUG_OUT_FILE_NAME=./debug.txt'
Objects = 'main.cpp SUtils.cpp'

def build(Name, Objects, Flags):
    os.system('g++' + ' ' + Flags + ' ' + '-o' + ' ' + Name + ' ' + Objects)

if len(sys.argv) > 1 and sys.argv[1] == 'Clean':
    os.system('git clean -dfX')
else:
    build(Name1, Objects, CommonFlags + ' -O0')
    build(Name2, Objects, CommonFlags + ' -O3')
