compiler=g++

name=my-utf8-to-upper

all : main.cpp
	$(compiler) -Wall -Wextra -Werror -pedantic -g -O0 -Wno-multichar -std=c++11 -o $(name) main.cpp

clean :
	rm -f $(name) $(name).exe
