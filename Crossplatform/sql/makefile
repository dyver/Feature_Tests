CCC=g++
FLAGS= -Wall -O3 -std=c++0x -pedantic
NAME=sql
OBJECTS=main.cpp
LIBS=-lpqxx

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)
