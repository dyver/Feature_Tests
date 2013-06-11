CCC=g++
FLAGS= -Wall -O0 -g -std=c++0x -pedantic -I./ -I../../libdlog/include
LIBRARYS= -ldlog -L../../libdlog/.libs
NAME=message
OBJECTS=message.cpp main.cpp

all:	main

main:	message.cpp
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBRARYS)

clean :
	rm -f $(NAME) *.creator.user
