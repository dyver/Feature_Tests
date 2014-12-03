#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys

Name = 'sigslot'
Flags = '-std=c++11 -Wall -Wextra -Werror -pedantic-errors -O3'
Objects = 'signals.cpp'

if len(sys.argv) > 1 and sys.argv[1] == 'Clean':
    os.system('git clean -dfX')
else:
    os.system('g++' + ' ' + Flags + ' ' + '-o' + ' ' + Name + ' ' + Objects)
