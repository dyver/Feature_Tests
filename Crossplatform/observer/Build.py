#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys

Name = 'observer'
Flags = '-std=c++98 -Wall -Wextra -Werror -pedantic-errors -O3'
Objects = 'main.cpp'

if len(sys.argv) > 1 and sys.argv[1] == 'Clean':
    os.system('git clean -dfX')
else:
    os.system('g++' + ' ' + Flags + ' ' + '-o' + ' ' + Name + ' ' + Objects)
