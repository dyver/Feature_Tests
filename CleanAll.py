#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
import os
import glob
import subprocess

sys.dont_write_bytecode = True

if sys.platform[:5] == 'linux':
    Trash = open('/dev/null', 'w')
else:
    Trash = open('nul', 'w')

print 'Cleaning targets ...',

StartDir = os.getcwd()
ThisScriptPath = os.path.abspath(sys.argv[0])
for Dir, _, Files in os.walk(StartDir):
    for i in Files:
        FilePath = Dir + '/' + i
        if ThisScriptPath == os.path.abspath(FilePath):
            continue
        if i == 'Clean.py':
            os.chdir(Dir)
            subprocess.call(["python", FilePath, ], stdout=Trash, stderr=Trash)
            os.chdir(StartDir)

print 'done.'
