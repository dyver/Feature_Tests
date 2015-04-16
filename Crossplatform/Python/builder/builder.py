#!/usr/bin/env python2
# -*- coding: utf-8 -*-


import os
import sys
import shutil


def rm(path):
    if os.path.isfile(path):
        os.remove(path)
        return()
    if os.path.isdir(path):
        shutil.rmtree(path, True)
        return()


def builder():

    def create_sources():
        rm('build-py')
        os.mkdir('build-py')
        os.chdir('build-py')

        program_text = '''
            #include <QApplication>
            #include <QMainWindow>

            int main(int argc, char* argv[]) {
                QApplication application(argc, argv);
                QMainWindow mainWindow;
                mainWindow.setWindowTitle("Welcome to Python!");
                mainWindow.setFixedWidth(350);
                mainWindow.setFixedHeight(200);
                mainWindow.show();
                return application.exec();
            }
        '''

        if os.access('main.cpp', os.F_OK):
            os.remove('main.cpp')

        with open('main.cpp', 'w') as program_source:
            program_source.write(program_text)

    def create_pro_file():
        os.system('qmake -project')

        pro_file_addon = '''

            greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
            CONFIG-=debug_and_release
            CONFIG+=release
            CONFIG+=silent
        '''

        with open('build-py.pro', 'a') as pro_file:
            pro_file.write(pro_file_addon)

    def build():
        os.system('qmake')
        os.system('make')

    def run():
        os.system('"' + os.getcwd() + '/build-py' + '"')

    create_sources()
    create_pro_file()
    build()
    run()

if __name__ == '__main__':
    builder()
