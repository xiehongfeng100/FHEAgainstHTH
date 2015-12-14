#ifndef FULLADDER_H
#define FULLADDER_H

#include <systemc.h>
#include <math.h>
#include "common.h"
using namespace std;

SC_MODULE(fulladder)
{
	sc_in<sc_uint<INPUTSIZE> > A_sc;
	sc_in<sc_uint<INPUTSIZE> > B_sc;
	sc_in<sc_uint<CARRYSIZE> > Cin_sc;
	sc_out<sc_uint<OUTPUTSIZE> > S_sc;
	sc_out<sc_uint<CARRYSIZE> > Cout_sc;

	void fullAdd()
	{
		// Temp varibles
		vector<int> A, B, S;
		int Cin, Cout;
		vector<LWE::CipherText> cipherOfA, rcipherOfA, cipherOfB, rcipherOfB, cipherOfC;
		vector<LWE::CipherText> cipherEvaOfAB, rcipherEvaOfAB, cipherEvaOfC;
		// Resizing
		// A.resize(INPUTSIZE);
		// B.resize(INPUTSIZE);
		// S.resize(INPUTSIZE);

		// cipherOfA.resize(INPUTSIZE);
		// rcipherOfA.resize(INPUTSIZE);
		// cipherOfB.resize(INPUTSIZE);
		// rcipherOfB.resize(INPUTSIZE);

		// cipherEvaOfAB.resize(INPUTSIZE);
		// rcipherEvaOfAB.resize(INPUTSIZE);

		// cipherOfC.resize(INPUTSIZE + 1);
		// rcipherOfC.resize(INPUTSIZE + 1);
		
		// Read A, B and C
		A = int2bin(A_sc.read());
		B = int2bin(B_sc.read());
		Cin = Cin_sc.read();
		
		// Encrypt data
		enc(A, B, Cin, LWEsk, cipherOfA, rcipherOfA, cipherOfB, rcipherOfB, cipherOfC);

		// Evaluate cipher
		eva(Ek, cipherOfA, rcipherOfA, cipherOfB, rcipherOfB, cipherOfC,
				cipherEvaOfAB, rcipherEvaOfAB, cipherEvaOfC);

		// Decrypt data
		dec(LWEsk, cipherEvaOfAB, rcipherEvaOfAB, cipherEvaOfC, S, Cout);

		// Write data
		S_sc.write(bin2int(S));
		Cout_sc.write(Cout);

	}

	SC_CTOR(fulladder)
	{
		SC_METHOD(fullAdd);
		sensitive << A_sc << B_sc << Cin_sc;
	}

};


#endif
