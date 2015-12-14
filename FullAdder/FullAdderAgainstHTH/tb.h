#ifndef TB_H
#define TB_H

#include <systemc.h>
#include "common.h"

SC_MODULE(tb)
{
	sc_out<sc_uint<INPUTSIZE> > A_sc;
	sc_out<sc_uint<INPUTSIZE> > B_sc;
	sc_out<sc_uint<CARRYSIZE> > Cin_sc;
	sc_in<sc_uint<OUTPUTSIZE> > S_sc;
	sc_in<sc_uint<CARRYSIZE> > Cout_sc;
	sc_in_clk clk;

	void writeData(unsigned int A, unsigned int B, unsigned int Cin)
	{
		wait();
		A_sc = A;
		B_sc = B;
		Cin_sc = Cin;
	}

	void genInput()
	{
		writeData(0, 0, 0);
		writeData(0, 0, 1);
		writeData(1, 0, 0);
		writeData(0, 1, 0);
		writeData(1, 0, 1);
		writeData(0, 0, 1);
		writeData(1, 0, 0);
		
		writeData(128, 1, 0);
		writeData(128, 0, 1);

	}

	void displayVariable()
	{
		cout << "A = " << A_sc << ", B = " << B_sc << ", Cin = " << Cin_sc << endl;
		cout << "S = " << S_sc << ", Cout = " << Cout_sc << endl;
	}
	
	SC_CTOR(tb)
	{
		SC_CTHREAD(genInput, clk.pos());
		SC_METHOD(displayVariable);
		sensitive << A_sc << B_sc << Cin_sc << S_sc << Cout_sc;
		dont_initialize();
	}

};

#endif
