#!/usr/bin/python
# -*- coding: utf-8 -*-

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

Name = 'leak'
Flags = '-std=c++11 -Wall -Wextra -pedantic-errors -O3'
Objects = 'main.cpp'

if len(sys.argv) > 1 and sys.argv[1] == 'Clean':
    os.system('git clean -dfX')
else:
    os.system('g++' + ' ' + Flags + ' ' + '-o' + ' ' + Name + ' ' + Objects)
