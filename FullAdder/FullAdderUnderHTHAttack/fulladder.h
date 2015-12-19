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
		int S;
		int Cin, Cout;
	
		Cin = Cin_sc.read();
		// Attack
		if(Cin == 1)
			Cin = 0;

		int sum = A_sc.read() + B_sc.read() + Cin;
		vector<int> sumVec = int2bin(sum);
		if(sumVec.size() == 9)
		{
			Cout = sumVec[8];
			sumVec.resize(8);
			S = bin2int(sumVec);
		}
		else
		{
			Cout = 0;
			S = sum;
		}

		// Write data
		S_sc.write(S);
		Cout_sc.write(Cout);

	}

	SC_CTOR(fulladder)
	{
		SC_METHOD(fullAdd);
		sensitive << A_sc << B_sc << Cin_sc;
	}

};


#endif
