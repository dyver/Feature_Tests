CCC=gcc
FLAGS= -Wall -O3 -std=c89 -pedantic
NAME=pthread
OBJECTS=main.c
LIBS=-lpthread

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME) $(NAME).exe
