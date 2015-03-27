#ifndef NAND_H
#define NAND_H

#include <systemc.h>
#include <math.h>

SC_MODULE(nand)
{
	sc_in<bool> A;
	sc_in<bool> B;
	sc_out<bool> F;

	void do_nand()
	{
		F = !(A & B);
	}

	SC_CTOR(nand)
	{
		SC_METHOD(do_nand);
		sensitive << A << B;
	}

};

#endif
