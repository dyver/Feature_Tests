# OS type
isLinux=0
[ -x /proc ] && isLinux=1

# Compiler
compiler_path=/opt/gcc-4.9
#compiler_path=/opt/gcc-4.8.0
#compiler_path=/usr
compiler=$compiler_path/bin/g++
compiler_lib_path=$compiler_path/lib

# Standard
standard=c++1y
