CCC=g++
#CCC=arm-g++
FLAGS= -Wall -g -O0 -pedantic
NAME=sound
OBJECTS=main.cpp
LIBS=-lasound

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME) $(NAME).exe
