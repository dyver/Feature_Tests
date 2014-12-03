#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import shutil
import multiprocessing
import datetime

MakeThreadsMaximum = multiprocessing.cpu_count() + 1

Flags = '-std=c++11 -Wall -Wextra -Werror -pedantic-errors -O3'
Name = 'multi-thread-make'

ModuleHeader = [
    '#include <map>',
    '#include <iostream>',
    '',
    'using namespace std;',
    ''
]

ModuleFooter = [
    '    map<string, string> music;',
    '    music["Madonna"] = "Virgin";',
    '    for (auto item : music) cout << item.first << item.second << endl;',
    '}',
]

def generate():
    if os.path.isdir('build'):
        shutil.rmtree('build', True)
    os.mkdir('build')
    os.chdir('build')

    with open('main.cpp', 'w') as FileHandle:
        FileHandle.write('#include <iostream>\n\n')
        for Index in xrange(1, MakeThreadsMaximum):
            FileHandle.write('extern void function' + str(Index) + '();\n')
        FileHandle.write('\nusing namespace std;\n\n')
        FileHandle.write('int main() {\n')
        FileHandle.write('    cout << "Main" << endl;\n')
        for Index in xrange(1, MakeThreadsMaximum):
            FileHandle.write('    function' + str(Index) + '();\n')
        FileHandle.write('\n    return 0;\n')
        FileHandle.write('}\n')

    for Index in xrange(1, MakeThreadsMaximum):
        FileName = 'file' + str(Index) + '.cpp'
        with open(FileName, 'w') as FileHandle:
            for Line in ModuleHeader:
                FileHandle.write(Line)
                FileHandle.write('\n')
            FileHandle.write('void function' + str(Index) + '() {\n')
            for Line in ModuleFooter:
                FileHandle.write(Line)
                FileHandle.write('\n')

    with open('Makefile', 'w') as FileHandle:
        FileHandle.write('FLAGS=' + Flags + '\n\n')
        FileHandle.write('all:\tmain.o ')
        for Index in xrange(1, MakeThreadsMaximum):
            FileHandle.write('file' + str(Index) + '.o ')
        FileHandle.write('\n')
        FileHandle.write('\tg++ -o ' + Name + ' main.o ')
        for Index in xrange(1, MakeThreadsMaximum):
            FileHandle.write('file' + str(Index) + '.o ')
        FileHandle.write('\n\n')
        FileHandle.write('clean:\n')
        FileHandle.write('\trm -rf main.o ')
        for Index in xrange(1, MakeThreadsMaximum):
            FileHandle.write('file' + str(Index) + '.o ')
        FileHandle.write(Name)
        FileHandle.write('\n\n')
        FileHandle.write('main.o:\tmain.cpp\n')
        FileHandle.write('\tg++ -c main.cpp -o main.o $(FLAGS)\n\n')
        for Index in xrange(1, MakeThreadsMaximum):
            FileHandle.write('file' + str(Index) + '.o:\tfile' + str(Index) + '.cpp\n')
            FileHandle.write('\tg++ -c file' + str(Index) + '.cpp -o')
            FileHandle.write(' file'+ str(Index) + '.o $(FLAGS)\n')
            FileHandle.write('\n')

    os.chdir(Root)

def endingsForm(Word, Number):
    if Number > 1:
        return Word + 's'
    return Word

def build(NumberOfMakeThreads):
    os.chdir('build')
    print '\n*** Building using', NumberOfMakeThreads, endingsForm('thread', NumberOfMakeThreads),
    print '***\n'
    Before = datetime.datetime.now()
    os.system('make -j' + str(NumberOfMakeThreads))
    After = datetime.datetime.now()
    Elapsed = After - Before
    print '\n*** Elapsed time:', Elapsed, '***\n'
    os.chdir(Root)
    if os.path.isdir('build'):
        shutil.rmtree('build', True)

if len(sys.argv) > 1 and sys.argv[1] == 'Clean':
    os.system('git clean -dfX')
else:
    Root = os.getcwd()
    generate()
    build(1)
    generate()
    build(MakeThreadsMaximum)
