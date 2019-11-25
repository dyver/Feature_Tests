CCC=g++
#CCC=arm-g++
FLAGS= -std=c++98 -Wall -Wextra -pedantic-errors -O3 -Wall -Wextra -Werror -g -O0 -pedantic
NAME=sound
OBJECTS=main.cpp
LIBS=-lasound

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME) $(NAME).exe
