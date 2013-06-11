CCC=arm-gcc
FLAGS= -Wall -O3
NAME_CLIENT=client
NAME_SERVER=server
OBJECTS_CLIENT=client.c
OBJECTS_SERVER=server.c

all:	client server

client:	$(OBJECTS_CLIENT)
	$(CCC) $(FLAGS) -o $(NAME_CLIENT) $(OBJECTS_CLIENT)

server:	$(OBJECTS_SERVER)
	$(CCC) $(FLAGS) -o $(NAME_SERVER) $(OBJECTS_SERVER)

clean:
	rm $(NAME_CLIENT)
	rm $(NAME_SERVER)
