CCC=g++
FLAGS= -Wall -g -O0 -std=c++0x -pedantic -I/home/sergey/.distrib/include
NAME=arclistener
OBJECTS=main.cpp
LIBS=-lpqxx -lpthread -L/home/sergey/.distrib/.x86/.debug/lib -lravarc -lravdata -ljpeg -lravdlog

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)
