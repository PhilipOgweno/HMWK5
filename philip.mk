# My makefile for Programm Homework4.cpp
# the compiler to use.
CC = g++
CFLAGS = -Wall

all: hw5

hw5: philip.cpp

	${CC} ${CFLAGS} philip.cpp -o philip

clean:
	rm  -rf philip
