#!/usr/bin/env python2
# -*- coding: utf-8 -*-


import sys
import os
import subprocess


print 'Running program using <os.system> ...'
os.system('python2 script.py "Argument with spaces" 2-nd')

print 'Running program using <subprocess.call> ...'
subprocess.call(['python2', 'script.py', 'First argument', '2'])

print 'Importing module ...'
sys.dont_write_bytecode = True
import script
script.test()
