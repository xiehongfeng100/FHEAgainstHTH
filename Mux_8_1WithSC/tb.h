#ifndef TB_H
#define TB_H

#include <systemc.h>
#include "common.h"

SC_MODULE(tb)
{
	sc_out<sc_uint<INPUTSIZE> > dataIn;
	sc_out<sc_uint<SELECTSIZE> > selIn;
	sc_in<sc_uint<OUTPUTSIZE> > dataOut;
	sc_in_clk clk;

	void gen_input()
	{	
		wait(); dataIn.write(0xC8); selIn.write(0x0);
		wait(); dataIn.write(0xC8); selIn.write(0x1);
		wait(); dataIn.write(0xC8); selIn.write(0x2);
		wait(); dataIn.write(0xC8); selIn.write(0x3);
		wait(); dataIn.write(0xC8); selIn.write(0x4);
		wait(); dataIn.write(0xC8); selIn.write(0x5);
		wait(); dataIn.write(0xC8); selIn.write(0x6);
		wait(); dataIn.write(0xC8); selIn.write(0x7);
	}

	void display_variable()
	{
		cout << "dataIn = " << dataIn << ", selIn = " << selIn << ", dataOut = " << dataOut << endl;
	}
	
	SC_CTOR(tb)
	{
		SC_CTHREAD(gen_input, clk.pos());
		SC_METHOD(display_variable);
		sensitive << dataOut << dataIn << selIn;
		dont_initialize();
	}

};

#endif
