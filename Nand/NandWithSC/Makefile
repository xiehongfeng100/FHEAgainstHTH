LIB_DIR=-L/usr/local/systemc-2.3.1/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.1/include
LIB=-lsystemc-2.3.1

CC=g++
CFLAGS=-Wall -g
EXE=main

all:
	$(CC) $(CFLAGS) -o $(EXE) nand.h tb.h main.cpp $(LIB_DIR) $(INC_DIR) $(LIB)

.PHONY:clean
clean:
	rm -rf *.o $(EXE)
