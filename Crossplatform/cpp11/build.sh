#!/bin/bash

#compiler=/opt/gcc-4.8.0/bin/g++
compiler=/opt/gcc-4.9/bin/g++
#compiler=g++

compile_item() {
    local root_path=$1
    local container=$2
    local name=$3
    local flags="-c -std=c++1y -pedantic-errors -Wall -Wextra -Werror -g -O0"
    local includes_path=$root_path/include
    local src_file=$name.cpp
    local src_file_path=$root_path$container$src_file
    local obj_file=$name.o
    local obj_file_path=$root_path/bin/$obj_file
    [ -f "$obj_file_path" ] `rm -f "$obj_file_path"`
    $compiler $flags -I"$includes_path" -o "$obj_file_path" "$src_file_path" 2>> "$compiler_output"
    return $?
}

compile_all() {
    local root_dir=$1
    mkdir -p $root_dir/bin
    for item in `ls *.cpp` ; do
        obj=${item%.cpp} # use filename but extension
        compile_item "$root_dir" "/src/" $obj
        if [ $? != 0 ] ; then
            echo -e $red"[FAIL] "$cyan$obj$default" replaced by proxy."
            compile_item "$root_dir" "/proxies/" $obj
        else
            echo -e $green"[ OK ] "$cyan$obj$default" compiled successfully."
        fi
    done
}

link_objects() {
    local name=$1
    local objects=""
    for item in `ls *.cpp` ; do
        objects=$objects" ../bin/"${item%.cpp}.o
    done
    local flags=""
    if [ $isLinux = 1 ] ; then
        flags=$flags" -pthread"
    fi
    local target="../bin/"$name
    $compiler $flags $objects -o $target 2>> "$compiler_output"
    if [ $? != 0 ] ; then
        echo -e $red"Linking failed"$default
        return 1
    else
        echo -e $magenta"Linking done"$default
        return 0
    fi
}

black='\E[30m'
red='\E[31m'
green='\E[32m'
yellow='\E[33m'
blue='\E[34m'
magenta='\E[35m'
cyan='\E[36m'
white='\E[37m'
default='\E[0m'

isLinux=0
[ -x /proc ] && isLinux=1

target=$1
[ -z $target ] && target=all
case "$target" in
    all)
        echo -e $magenta"Building target using "`$compiler --version | grep "g++"`$default
        root_dir=$PWD
        compiler_output=$root_dir/compiler_output.txt
        [ -f "$compiler_output" ] `rm -f "$compiler_output"`
        echo "" > "$compiler_output"
        cd ./src/
        compile_all "$root_dir"
        if [ $isLinux = 1 ] ; then
            link_objects cpp11.elf
        else
            link_objects cpp11.exe
        fi
        result=$?
        cd ../
        if [ $result != 0 ] ; then
            echo -e $red"Building failed"$default
            exit 1
        else
            echo -e $magenta"Building done"$default
            exit 0
        fi
        ;;
    clean)
        echo -e $magenta"Cleaning target"$default
        rm -f ./*.creator.user
        rm -f ./compiler_output.txt
        cd ./bin/
        rm -f ./*.*
        cd ../
        echo -e $magenta"Cleaning done"$default
        exit 0
        ;;
esac
