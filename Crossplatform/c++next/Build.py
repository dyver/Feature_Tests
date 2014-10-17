#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import subprocess

sys.dont_write_bytecode = True

import Defines

from Defines import Compiler
from Defines import Standard

if sys.platform[:5] == 'linux':
    IsLinix = True
else:
    IsLinix = False

def compileItem(Dir, Item):
    SrcFileName = Item + '.cpp'
    SrcFile = Dir + '/' + SrcFileName
    ObjFileName = Item + '.o'
    ObjFile = BinaryDir + '/' + ObjFileName
    Command = [
        Compiler,
        '-c',
        '-std=' + Standard,
        '-pedantic-errors',
        '-Wall',
        '-Wextra',
        '-Werror',
        '-g',
        '-O0',
        '-I' + IncludesDir,
        '-o' + ObjFile,
        SrcFile
    ]
    if os.path.isfile(ObjFile):
        os.remove(ObjFile)
    with open(CompilerOutput, "ab") as fd:
        return subprocess.call(
            Command,
            stdout=fd,
            stderr=fd
        )

def compileAll(RootDir):
    if not os.path.isdir(BinaryDir):
        os.mkdir(BinaryDir)
    List = []
    for Item in os.listdir('src'):
        if Item.endswith('.cpp'):
            List.append(Item[:-4])
    List.sort()
    for Object in List:
        if compileItem(SourcesDir, Object) != 0:
            print '[FAIL] {' + Object + '} replaced by proxy.'
            compileItem(ProxiesDir, Object)
        else:
            print '[ OK ] {' + Object + '} compiled successfully.'

def linkObjects():
    Command = [ Compiler ]
    for Item in os.listdir(BinaryDir):
        if Item.endswith('.o'):
            Command.append(BinaryDir + '/' + Item)
    if IsLinix:
        Command.append('-pthread')
    Command.append('-o' + BinaryFile)
    with open(CompilerOutput, "ab") as fd:
        if subprocess.call(
            Command,
            stdout=fd,
            stderr=fd
        ) != 0:
            print 'Linking failed'
        else:
            print 'Linking done'

def build():
    if IsLinix:
        CompilerFile = Compiler
    else:
        CompilerFile = Compiler + '.exe'
    if not os.path.isfile(CompilerFile):
        print 'ERROR: Specified compiler {' + Compiler + '} not present in system.'
        exit(1)
    if os.path.isfile(CompilerOutput):
        os.remove(CompilerOutput)
    compileAll(RootDir)
    linkObjects()

def clean():
    os.system('git clean -dfX')

def run():
    os.system(BinaryFile)

def makeProxies():
    if not os.path.isdir(ProxiesDir):
        os.mkdir(ProxiesDir)
    for Item in os.listdir(ProxiesDir):
        os.remove(ProxiesDir + '/' + Item)
    for Item in os.listdir(SourcesDir):
        if Item == '++c.cpp':
            continue
        if Item.endswith('.cpp'):
            with open(ProxiesDir + '/' + Item, "ab") as fd:
                fd.write('#include <++c.h>\n\n')
                fd.write('void ' + Item[:-4] + '() {\n')
                fd.write('    std::cout << std::endl << \"Feature \\\"' + Item[:-4] + '\\\" not implemented.\" << std::endl;\n')
                fd.write('}\n')

def makeDeclarations():
    DeclarationsFile = IncludesDir + '/declarations.h'
    if os.path.isfile(DeclarationsFile):
        os.remove(DeclarationsFile)
    with open(DeclarationsFile, "ab") as fd:
        fd.write('#ifndef DECLARATIONS_H\n')
        fd.write('#define DECLARATIONS_H\n\n')
        for Item in sorted(os.listdir(ProxiesDir), key=str.lower):
            if Item == '++c.cpp':
                continue
            if Item.endswith('.cpp'):
                fd.write('void ' + Item[:-4] + '();\n')
        fd.write('\n#endif // DECLARATIONS_H\n')

RootDir = os.getcwd()
Name = os.path.basename(RootDir)
if IsLinix:
    BinaryFileName = Name + '.elf'
else:
    BinaryFileName = Name + '.exe'
BinaryDir = RootDir + '/bin'
BinaryFile = BinaryDir + '/' + BinaryFileName
SourcesDir = RootDir + '/src'
ProxiesDir = RootDir + '/proxies'
IncludesDir = RootDir + '/include'
CompilerOutput = RootDir + '/CompilerOutput.txt'

if len(sys.argv) > 1:
    if sys.argv[1] == 'Build':
        build()
    if sys.argv[1] == 'Clean':
        clean()
    if sys.argv[1] == 'Run':
        run()
    if sys.argv[1] == 'MakeProxies':
        makeProxies()
    if sys.argv[1] == 'MakeDeclarations':
        makeDeclarations()
else:
    clean()
    build()
