#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import subprocess

Name = 'hello'
ProjectFileName = Name + '.pro'

def Clean():
    os.system('git clean -dfX')

def Build():
    os.system('qmake')
    os.system('make')

def Run():
    subprocess.call([Name, '-style', 'windows'])
    subprocess.call([Name, '-style', 'windowsxp'])
    subprocess.call([Name, '-style', 'macintosh'])
    subprocess.call([Name, '-style', 'motif'])
    subprocess.call([Name, '-style', 'plastique'])
    subprocess.call([Name, '-style', 'cde'])

def Project():
        Clean()
        if os.path.isfile(ProjectFileName):
            os.remove(ProjectFileName)
        os.system('qmake -project')
        with open(ProjectFileName, 'ab') as f:
            f.write('QT *= widgets\n')
            f.write('CONFIG *= silent\n')
            f.write('CONFIG -= debug_and_release\n')
            f.write('windows : CONFIG *= console\n')
            f.write('QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra -Werror\n')
        os.system('qmake')

if len(sys.argv) > 1:
    if sys.argv[1] == 'Clean':
        Clean()
    if sys.argv[1] == 'Project':
        Clean()
        Project()
    if sys.argv[1] == 'Run':
        Run()
else:
    Clean()
    Project()
    Build()
