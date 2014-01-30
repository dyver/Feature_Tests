#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import shutil
import sys

from colorama import init
init(autoreset=True)
from colorama import Fore, Back, Style
print Fore.RED + Style.BRIGHT + 'some red text'
print(Back.GREEN + 'and with a green background')
print(Style.DIM + 'and in dim text')
print(Fore.RESET + Back.RESET + Style.RESET_ALL)
try:
    print u"Вернулись обратно back to normal now"
except:
    print "Fatal error:", sys.exc_info()[0], sys.exc_info()[1]

if os.path.exists('build-py'):
    shutil.rmtree('build-py', True)
os.mkdir('build-py')
os.chdir('build-py')

program_text = [
    '#include <QMainWindow>',
    '#include <QApplication>',
    '',
    'int main(int argc, char *argv[]) {',
    '    QApplication a(argc, argv);',
    '    QMainWindow w;',
    '    w.setWindowTitle("Welcome to Python!");',
    '    w.setMinimumWidth(300);',
    '    w.show();',
    '    return a.exec();',
    '}'
]

if os.access('main.cpp', os.F_OK):
    os.remove('main.cpp')

with open('main.cpp', 'w') as f:
    for i in program_text:
        f.write(i)
        f.write('\n')

os.system('qmake -project')
with open('build-py.pro', 'a') as f:
    f.write('\ngreaterThan(QT_MAJOR_VERSION, 4): QT += widgets')
    f.write('\nCONFIG-=debug_and_release')
    f.write('\nCONFIG+=release')
    f.write('\nCONFIG+=silent')

os.system('qmake')
os.system('make')
print os.getcwdu()
os.system('"' + os.getcwd() + '/build-py' + '"')
