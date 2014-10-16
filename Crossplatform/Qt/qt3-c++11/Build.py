#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import sys
import subprocess

Name = 'qt3-c++11'
ProjectFileName = Name + '.pro'

def Clean():
    os.system('git clean -dfX')

def Build():
    os.environ['QTDIR'] = '/opt/qt3'
    os.environ['PATH'] = os.environ['QTDIR'] + '/bin:' + os.environ['PATH']
    if 'LD_LIBRARY_PATH' in os.environ:
        LD_LIBRARY_PATH = os.environ['LD_LIBRARY_PATH']
    else:
        LD_LIBRARY_PATH = ''
    os.environ['LD_LIBRARY_PATH'] = os.environ['QTDIR'] + '/lib:' + LD_LIBRARY_PATH
    os.system('qmake')
    os.system('make')

def Run():
    subprocess.call(['./' + Name])

if len(sys.argv) > 1:
    if sys.argv[1] == 'Build':
        Build()
    if sys.argv[1] == 'Clean':
        Clean()
    if sys.argv[1] == 'Run':
        Run()
else:
    Clean()
    Build()
