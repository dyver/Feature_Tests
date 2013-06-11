# Makefile for libconfig - examples


all:	sample1 sample2 sample3 stub

sample1:	sample1.cpp
	$(CC) -o $@  $< `pkg-config --cflags libconfig++` `pkg-config --libs libconfig++`

sample2:	sample2.cpp
	$(CC) -o $@  $< `pkg-config --cflags libconfig++` `pkg-config --libs libconfig++`

sample3:	sample3.cpp
	$(CC) -o $@  $< `pkg-config --cflags libconfig++` `pkg-config --libs libconfig++`

stub:	stub.cpp
	$(CC) -o $@  $< `pkg-config --cflags libconfig++` `pkg-config --libs libconfig++`

clean:
	rm -f sample1 sample2 sample3 stub