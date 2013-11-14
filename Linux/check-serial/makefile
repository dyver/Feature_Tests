native:
	compiler=g++; \
	NAME=check-serial; \
	FLAGS="-Wall -g -O0 -std=c++11 -pedantic -Wall -Wextra -Werror"; \
	LIBS=-lpthread; \
	OBJECTS=main.cpp; \
	$$compiler $$FLAGS -o $$NAME $$OBJECTS $$LIBS

armv5:
	compiler=armv5tel-softfloat-linux-gnueabi-g++; \
	NAME=check-serial_armv5; \
	FLAGS="-Wall -g -O0 -std=c++11 -pedantic -Wall -Wextra -Werror"; \
	LIBS=-lpthread; \
	OBJECTS=main.cpp; \
	$$compiler $$FLAGS -o $$NAME $$OBJECTS $$LIBS

armv7:
	compiler=armv7a-hardfloat-linux-gnueabi-g++; \
	NAME=check-serial_armv7; \
	FLAGS="-Wall -g -O0 -std=c++11 -pedantic -Wall -Wextra -Werror"; \
	LIBS=-lpthread; \
	OBJECTS=main.cpp; \
	$$compiler $$FLAGS -o $$NAME $$OBJECTS $$LIBS

all: native

clean:
	rm $(NAME)
