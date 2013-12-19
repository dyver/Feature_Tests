#!/bin/bash

rm -f ./android
rm -f ./Makefile*
rm -f ./*.o
rm -fr ./debug
rm -fr ./release
rm -f *.pro.user
find -type f -name "*~" | (
	while read item ; do
			rm -f "$item"
	done
)
