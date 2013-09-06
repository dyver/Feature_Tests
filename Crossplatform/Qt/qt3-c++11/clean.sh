#!/bin/bash

rm -f ./qt3-c++11
rm -f ./Makefile*
rm -f ./*.o
rm -fr ./debug
rm -fr ./release
rm -f *.pro.user
rm -f moc_*.cpp
find -type f -name "*~" | (
	while read item ; do
			rm -f "$item"
	done
)
