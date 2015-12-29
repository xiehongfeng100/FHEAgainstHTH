#ifndef MUX_8_1_H
#define MUX_8_1_H

#include <systemc.h>
#include <math.h>
#include "common.h"

SC_MODULE(mux_8_1)
{
	sc_in<sc_uint<ENABLESIZE> > en_n;
	sc_in<sc_uint<INPUTSIZE> > dataIn;
	sc_in<sc_uint<SELECTSIZE> > selIn;
	sc_out<sc_uint<OUTPUTSIZE> > dataOut;
	sc_out<sc_uint<OUTPUTSIZE> > flag;

	void do_mux()
	{
		// Read en_n
		int en = en_n.read();

		// Read dataIn
		vector<int> data_8;
		data_8.resize(8);
		data_8 = int2bin(dataIn.read());

		// Read selIn
		int sel_3 = selIn.read();

		// Decrypt dataOut
		int selected = data_8[sel_3];
		int out;	
		if(en || selected)
		{
			out = 0;
		}
		else
		{
			out = selected;
		}
		dataOut.write(out);

		// Set flag
		int tmpFlag = en * out;
		flag.write(tmpFlag);

	}

	SC_CTOR(mux_8_1)
	{
		SC_METHOD(do_mux);
		sensitive << en_n << dataIn << selIn;
	}

};

#endif
