#!/usr/bin/env python2
# -*- coding: utf-8 -*-

def compileItem(Directory, Item):
    SourceFileName = Item + '.cpp'
    SourceFile = Directory + '/' + SourceFileName
    ObjectFileName = Item + '.o'
    ObjectFile = BinaryDirectory + '/' + ObjectFileName
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
        '-I' + IncludesDirectory,
        '-o' + ObjectFile,
        SourceFile
    ]
    if os.path.isfile(ObjectFile):
        os.remove(ObjectFile)
    with open(CompilerOutput, 'ab') as OutputHandle:
        return subprocess.call(
            Command,
            stdout=OutputHandle,
            stderr=OutputHandle
        )


def compileAll(RootDirectory):
    if not os.path.isdir(BinaryDirectory):
        os.mkdir(BinaryDirectory)
    ObjectsList = []
    for Item in os.listdir('src'):
        if Item.endswith('.cpp'):
            ObjectsList.append(Item[:-4])
    ObjectsList.sort()
    for Object in ObjectsList:
        if compileItem(SourcesDirectory, Object) != 0:
            print '[FAIL] {' + Object + '} replaced by proxy.'
            compileItem(ProxiesDirectory, Object)
        else:
            print '[ OK ] {' + Object + '} compiled successfully.'


def linkObjects():
    Command = [ Compiler ]
    for Item in os.listdir(BinaryDirectory):
        if Item.endswith('.o'):
            Command.append(BinaryDirectory + '/' + Item)
    if IsLinix:
        Command.append('-pthread')
    Command.append('-o' + BinaryFile)
    with open(CompilerOutput, 'ab') as OutputHandle:
        if subprocess.call(
            Command,
            stdout=OutputHandle,
            stderr=OutputHandle
        ) != 0:
            print 'Linking failed.'
        else:
            print 'Linking done.'


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
    compileAll(RootDirectory)
    linkObjects()


def clean():
    os.system('git clean -dfX')


def run():
    subprocess.call(BinaryFile)


def makeProxies():
    print 'Making proxies ...',
    sys.stdout.flush()
    if not os.path.isdir(ProxiesDirectory):
        os.mkdir(ProxiesDirectory)
    for Item in os.listdir(ProxiesDirectory):
        os.remove(ProxiesDirectory + '/' + Item)
    for Item in os.listdir(SourcesDirectory):
        if Item == '++c.cpp':
            continue
        if Item.endswith('.cpp'):
            with open(ProxiesDirectory + '/' + Item, 'ab') as OutputHandle:
                OutputHandle.write('#include <++c.h>\n\n')
                OutputHandle.write('void ' + Item[:-4] + '() {\n')
                OutputHandle.write('    std::cout << std::endl << \"Feature \\\"')
                OutputHandle.write(Item[:-4])
                OutputHandle.write('\\\" not implemented.\" << std::endl;\n')
                OutputHandle.write('}\n')
    print 'done.'


def makeDeclarations():
    print 'Making declarations ...',
    sys.stdout.flush()
    DeclarationsFile = IncludesDirectory + '/declarations.h'
    if os.path.isfile(DeclarationsFile):
        os.remove(DeclarationsFile)
    with open(DeclarationsFile, 'ab') as OutputHandle:
        OutputHandle.write('#ifndef DECLARATIONS_H\n')
        OutputHandle.write('#define DECLARATIONS_H\n\n')
        for Item in sorted(os.listdir(ProxiesDirectory), key=str.lower):
            if Item == '++c.cpp':
                continue
            if Item.endswith('.cpp'):
                OutputHandle.write('void ' + Item[:-4] + '();\n')
        OutputHandle.write('\n#endif // DECLARATIONS_H\n')
    print 'done.'


import os
import sys
import subprocess

sys.dont_write_bytecode = True
import Defines
from Defines import Compiler
from Defines import Standard


if sys.platform.startswith('linux'):
    IsLinix = True
else:
    IsLinix = False

RootDirectory = os.getcwd()
Name = os.path.basename(RootDirectory)
if IsLinix:
    BinaryFileName = Name + '.elf'
else:
    BinaryFileName = Name + '.exe'
BinaryDirectory = RootDirectory + '/bin'
BinaryFile = BinaryDirectory + '/' + BinaryFileName
SourcesDirectory = RootDirectory + '/src'
ProxiesDirectory = RootDirectory + '/proxies'
IncludesDirectory = RootDirectory + '/include'
CompilerOutput = RootDirectory + '/CompilerOutput.txt'


if len(sys.argv) > 1:
    if sys.argv[1] == 'Build':
        build()
    elif sys.argv[1] == 'Clean':
        clean()
    elif sys.argv[1] == 'Run':
        run()
    elif sys.argv[1] == 'MakeProxies':
        makeProxies()
    elif sys.argv[1] == 'MakeDeclarations':
        makeDeclarations()
    else:
        print 'Use one of \'Build\', \'Clean\', \'Run\', \'MakeProxies\' or \'MakeDeclarations\''
        exit(1)
else:
    clean()
    build()
