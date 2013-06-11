CCC=g++
#CCC=arm-g++
FLAGS= -Wall -O3 -std=c++98 -pedantic
NAME=pimpl
OBJECTS=main.cpp pimpl.cpp

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm $(NAME) $(NAME).exe
