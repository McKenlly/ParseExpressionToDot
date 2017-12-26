FLAGS=-std=c++11 -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -O2
CC=g++
LINK=-lm

all: clear main

main:  parser.cpp
	$(CC) $(FLAGS) -o parser parser.cpp 

clear:
	rm -f *.o
	rm -fr *.dSYM
