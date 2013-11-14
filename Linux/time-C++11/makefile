compiler=g++
# compiler=armv5tel-softfloat-linux-gnueabi-g++
compiler=armv7a-hardfloat-linux-gnueabi-g++

name=time-C++11

all : main.cpp
	$(compiler) -Wall -Wextra -pedantic -g -O0 -std=c++11 -pthread -o $(name) main.cpp

clean :
	rm -f $(name) $(name).exe
