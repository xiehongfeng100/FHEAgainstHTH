PREFIX=$(HOME)
CC=g++ -g
AR=ar
CFLAGS= -Wall -O3
LDFLAGS= -L. -lfhew -lfftw3 
INCLUDE=distrib.h LWE.h FHEW.h FFT.h params.h fulladder.h

all: libfhew.a main

clean:
	rm *.o main libfhew.a || echo nothing to clean

main: main.cpp libfhew.a
	$(CC) $(CFLAGS) -o main main.cpp $(LDFLAGS)

libfhew.a: distrib.o FFT.o LWE.o FHEW.o fulladder.o
	$(AR) -q libfhew.a distrib.o FFT.o LWE.o FHEW.o fulladder.o

distrib.o: distrib.cpp distrib.h params.h
	$(CC) $(CFLAGS) -c distrib.cpp

FFT.o: FFT.h FFT.cpp params.h FHEW.h
	$(CC) $(CFLAGS) -c FFT.cpp

LWE.o: LWE.h LWE.cpp FFT.h params.h distrib.h
	$(CC) $(CFLAGS) -c LWE.cpp

FHEW.o: FHEW.h FHEW.cpp FFT.h LWE.h params.h
	$(CC) $(CFLAGS) -c FHEW.cpp

fulladder.o: fulladder.h fulladder.cpp LWE.h FHEW.h
	$(CC) $(CFLAGS) -c fulladder.cpp

