#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys

Flags = '-std=gnu89 -Wall -Wextra -Werror -pedantic-errors -O3'
Name1 = 'sender'
Name2 = 'receiver'

def build(Name, Flags):
    os.system('gcc' + ' ' + Flags + ' ' + '-o' + ' ' + Name + ' ' + Name + '.c')

if len(sys.argv) > 1 and sys.argv[1] == 'Clean':
    os.system('git clean -dfX')
else:
    build(Name1, Flags)
    build(Name2, Flags)
