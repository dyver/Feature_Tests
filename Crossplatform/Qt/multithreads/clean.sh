#!/bin/bash

rm -f ./multithreads
rm -f ./Makefile*
rm -f ./*.o
rm -f *.qm
rm -f qrc_*.cpp
rm -f *.pro.user
rm -fr ./debug
rm -fr ./release
find -type f -name "*~" | (
	while read item ; do
			rm -f "$item"
	done
)
