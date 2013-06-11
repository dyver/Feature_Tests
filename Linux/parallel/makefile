CCC=g++
FLAGS= -Wall -g -O0 -std=c++0x -pedantic
NAME=parallel
OBJECTS=main.cpp parallel.cpp
LIBS=-lpthread

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME) *.creator.user
