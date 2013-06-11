#!/bin/bash

host_name="armv5tel-softfloat-linux-gnueabi"
build_name="i686-pc-linux-gnu"

./clean.sh

./autogen.sh
[ $? -ne 0 ] && echo "Making configure error" && exit 1

./configure --host $host_name --build $build_name
[ $? -ne 0 ] && echo "Configure error" && exit 1

make
