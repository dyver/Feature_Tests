#!/bin/bash

dir_list=".deps .libs m4 autom4te.cache build_dir"

for item in $dir_list ; do
    find . -type d -name $item -exec rm -rf {} 1> /dev/null 2> /dev/null \;
done

files_list="\
    *.a \
    *.o \
    *.la \
    *.lo \
    Makefile \
    Makefile.in \
    libtool \
    ltmain.sh \
    aclocal.m4 \
    acinclude.m4 \
    configure \
    configure.in \
    config.h \
    *config.h.in \
    config.guess \
    config.status \
    config.sub \
    config.log \
    depcomp \
    install-sh \
    missing \
    stamp-h1 \
    *.*~ \
    *.kate-swp \
    QtCr.*.creator.user \
    *.pro.user \
"
for item in $files_list ; do
    find . -type f -name $item -exec rm -rf {} 1> /dev/null 2> /dev/null \;
done

rm -fr autohell
