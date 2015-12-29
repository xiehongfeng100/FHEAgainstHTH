LIB_DIR=-L/usr/local/systemc-2.3.1/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.1/include
LIB=-lsystemc-2.3.1

CC=g++
CFLAGS=-Wall -g
EXE=main

main: common.h mux_8_1.h tb.h main.cpp	
	$(CC) $(CFLAGS) -o $(EXE) main.cpp $(LIB_DIR) $(INC_DIR) $(LIB)

.PHONY:clean
clean:
	rm $(EXE)|| echo nothing to clean
