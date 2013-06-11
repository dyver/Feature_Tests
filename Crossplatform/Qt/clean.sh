#!/bin/bash

list="\
    build-* \
"

for item in $list ; do
    rm -fr $item
done
