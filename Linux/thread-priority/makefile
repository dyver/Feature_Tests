compiler=g++

name=thread-priority

all : main.cpp
	$(compiler) -Wall -Wextra -Werror -pedantic -g -O0 -std=c++11 -pthread -o $(name) main.cpp

clean :
	rm -f $(name) $(name).exe
