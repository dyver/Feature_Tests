#!/usr/bin/env python2
# -*- coding: utf-8 -*-

Standard = 'c++14'
#Standard = 'c++11'

CompilerDirectory = '/usr'
#CompilerDirectory = 'c:/Qt/Qt5.4.1/Tools/mingw491_32'

#CrossCompiler = '/usr/bin/arm-linux-g++'


if 'CrossCompiler' in locals():
    Compiler = CrossCompiler
else:
    Compiler = CompilerDirectory + '/bin/g++'
