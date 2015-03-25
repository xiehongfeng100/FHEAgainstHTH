# FHEW 

## A Fully Homomorphic Encryption library

**version 1.0** -- *Release date: 2014.12.06*

**Authors:** Leo Ducas <leo@ducas.org> and Daniele Micciancio <daniele@cs.ucsd.edu>

FHEW is open-source software distributed under the terms of the GNU
General Public License. See the file LICENSE for complete details on the licensing of FHEW. 
The FHEW library is based on the Fully Homorphic Encryption scheme
described in the paper ["FHE bootstrapping in less than a second"](http://eprint.iacr.org/2014/816)
(L. Ducas and D. Micciancio, Cryptology  ePrint Archive 2014/816,)
and makes use of the [FFTW](http://www.fftw.org) library (the "Fastest
Fourier Transform in the West"). Hence the name FHEW, which you may
read as the "Fastest Homomorphic Encryption in the West", though the
name is more of a reference to FFTW than a claim about performance. The
library provides a symmetric encryption scheme to encrypt (and
decrypt) single bit messages, supporting the homomorphic evaluation of
arbitrary boolean circuits on encrypted data using a public (evaluation) key.

### Requirements 

FHEW requires the FFTW 3 library available at <http://www.fftw.org/download.html>, 
and a c++ compiler.  The library is written primarily in C, but a C++
compiler is needed  to support a few syntactical extensions (like
namespaces and reference parameters) used to improve the readibility
of the code.  Editing the library so to require just a c compiler
should be straightforward. The library has been tested using the g++
compiler from the  [GNU compiler collection](http://gcc.gnu.org) (gcc
version 4.9.1), but should work fine with other compilers as well.

### Installation

To build the library, just run ```make```.  This will produce a
library (libfhew.a), and a number of test/example programs. (See
below.) You can also run ``` make install``` to install the header
files and fhew library required to compile your own programs making
use of FHEW. By default, these are installed in $(HOME)/include and
$(HOME)/lib. Edit the Makefile to fit your needs. 

You can test the library by running the test program ```fhewTest```.
Running the test program with no arguments prints a simple usage message. 
