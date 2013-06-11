CCC=g++
FLAGS= -DDEBUG_LEVEL=0 -DDEBUG_OUT_DESTINATION=1 -DDEBUG_OUT_FILE_NAME=./debug.txt -Wall -O0
NAME=performanace
OBJECTS=main.cpp SUtils.cpp

all:	$(OBJECTS)
	$(CCC) $(FLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm $(NAME) $(NAME).exe
