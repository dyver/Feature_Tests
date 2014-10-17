#!/usr/bin/python
# -*- coding: utf-8 -*-

Standard = 'c++14'

CompilerDir = '/opt/gcc-4.9.1'
#CompilerDir = '/usr'
#CompilerDir = 'c:/Qt/Qt5.3.2/Tools/mingw482_32'
#CompilerDir = 'c:/mingw32'

#CrossCompiler = '/usr/bin/arm-linux-g++'

if 'CrossCompiler' in locals():
    Compiler = CrossCompiler
else:
    Compiler = CompilerDir + '/bin/g++'
