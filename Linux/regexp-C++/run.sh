#!/bin/bash

for Item in $(ls *.fb2) ; do
#    Name=$(iconv -f cp1251 -t utf8 "${Item}" | ./regexp-cpp)
    Name=$(cat "${Item}" | ./regexp-C++)
    mv "${Item}" "${Name}"
    echo ${Name}
done
