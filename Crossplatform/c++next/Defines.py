#!/usr/bin/env python2
# -*- coding: utf-8 -*-

#Standard = 'c++11'
#Standard = 'c++14'
#Standard = 'c++17'
Standard = 'c++2a'

CompilerDirectory = '/usr/bin/'
#CompilerDirectory = 'c:/Qt/Qt5.4.1/Tools/mingw491_32/bin/'

#CompilerPrefix = 'arm-linux-gnueabihf-'
#CompilerPrefix = 'i686-w64-mingw32-'
#CompilerPrefix = 'x86_64-w64-mingw32-'

CompilerPrefix  = CompilerPrefix if 'CrossCompiler' in locals() else ''

Compiler = CompilerDirectory + CompilerPrefix + 'g++'
