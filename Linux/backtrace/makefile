CCC=g++
FLAGS= -Wall -Wextra -Werror -pedantic -g -O0 -rdynamic
NAME=backtrace
OBJECTS=main.cpp

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)
