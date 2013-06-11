FLAGS=-Wall -Wextra -Werror -pedantic -std=c++11


all:	main.o file1.o file2.o file3.o file4.o file5.o file6.o file7.o file8.o
	g++ -o mtm main.o file1.o file2.o file3.o file4.o file5.o file6.o file7.o file8.o

clean:
	rm -rf main.o file1.o file2.o file3.o file4.o file5.o file6.o file7.o file8.o mtm*

main.o:	main.cpp
	g++ -c main.cpp -o main.o $(FLAGS)

file1.o:	file1.cpp
	g++ -c file1.cpp -o file1.o $(FLAGS)

file2.o:	file2.cpp
	g++ -c file2.cpp -o file2.o $(FLAGS)

file3.o:	file3.cpp
	g++ -c file3.cpp -o file3.o $(FLAGS)

file4.o:	file4.cpp
	g++ -c file4.cpp -o file4.o $(FLAGS)

file5.o:	file5.cpp
	g++ -c file5.cpp -o file5.o $(FLAGS)

file6.o:	file6.cpp
	g++ -c file6.cpp -o file6.o $(FLAGS)

file7.o:	file7.cpp
	g++ -c file7.cpp -o file7.o $(FLAGS)

file8.o:	file8.cpp
	g++ -c file8.cpp -o file8.o $(FLAGS)
