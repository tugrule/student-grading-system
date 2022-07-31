CC=g++
CFLAGS=-g -std=c++14

main: main.o menu.o student.o database.o
	$(CC) $(CFLAGS) -o main main.o menu.o student.o database.o

main.o: main.cpp menu.hpp student.hpp database.hpp
	$(CC) $(CFLAGS) -c main.cpp

student.o: student.hpp

database.o: database.hpp student.hpp

menu.o: menu.hpp database.hpp student.hpp

clean:
	rm *.o main