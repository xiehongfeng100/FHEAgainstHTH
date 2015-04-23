LIB_DIR=-L/usr/local/systemc-2.3.1/lib-linux64
INC_DIR=-I/usr/local/systemc-2.3.1/include
LIB=-lsystemc-2.3.1
LDFLAGS= -L. -lfhew -lfftw3 

CC=g++
CFLAGS=-Wall -g
AR=ar
EXE=main

all: libfhew.a main

main: nand.h tb.h main.cpp libfhew.a
	$(CC) $(CFLAGS) -o $(EXE) main.cpp $(LDFLAGS) $(LIB_DIR) $(INC_DIR) $(LIB)

libfhew.a: distrib.o FFT.o LWE.o FHEW.o mux_8_1.o
	$(AR) -q libfhew.a distrib.o FFT.o LWE.o FHEW.o mux_8_1.o

distrib.o: distrib.cpp distrib.h params.h
	$(CC) $(CFLAGS) -c distrib.cpp

FFT.o: FFT.h FFT.cpp params.h FHEW.h
	$(CC) $(CFLAGS) -c FFT.cpp

LWE.o: LWE.h LWE.cpp FFT.h params.h distrib.h
	$(CC) $(CFLAGS) -c LWE.cpp

FHEW.o: FHEW.h FHEW.cpp FFT.h LWE.h params.h
	$(CC) $(CFLAGS) -c FHEW.cpp

mux_8_1.o: mux_8_1.h mux_8_1.cpp LWE.h FHEW.h
	$(CC) $(CFLAGS) -c mux_8_1.cpp

.PHONY:clean
clean:
	rm *.o $(EXE) libfhew.a || echo nothing to clean
