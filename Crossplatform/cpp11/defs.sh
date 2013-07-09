# OS type
isLinux=0
[ -x /proc ] && isLinux=1

# Compiler
#compiler_path=/usr
#compiler_path=/opt/gcc-4.9-20130623
#compiler_path=/opt/gcc-4.8.0
#compiler_path=c:/mingw32
#compiler_path=c:/mingw64
#compiler_path=c:/Qt/Qt5.0.1/Tools/MinGW
compiler_path=c:/Qt/Qt5.1.0/Tools/mingw48_32
compiler=$compiler_path/bin/g++
compiler_lib_path=$compiler_path/lib

# Standard
standard=c++11
