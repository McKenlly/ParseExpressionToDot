FLAGS=-std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -O2
CC=g++
LINK=-lm

all: delete_main expressionTree main clear

main:  parser.cpp
	$(CC) $(FLAGS) -c parser.cpp
	$(CC) $(FLAGS) -o parser parser.o TreeExpresssion.o 

expressionTree: TreeExpresssion.cpp
	$(CC) $(FLAGS) -c TreeExpresssion.cpp

clear:
	rm -f *.o
	rm -fr *.dSYM

delete_main:
	rm parser
