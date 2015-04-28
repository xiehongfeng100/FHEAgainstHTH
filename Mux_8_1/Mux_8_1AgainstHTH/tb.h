#ifndef TB_H
#define TB_H

#include <systemc.h>
#include "common.h"

SC_MODULE(tb)
{
	sc_out<sc_uint<ENABLESIZE> > en_n;
	sc_out<sc_uint<INPUTSIZE> > dataIn;
	sc_out<sc_uint<SELECTSIZE> > selIn;
	sc_in<sc_uint<OUTPUTSIZE> > dataOut;
	sc_in<sc_uint<OUTPUTSIZE> > flag;
	sc_in_clk clk;

	void writeData(unsigned int en, unsigned int data, unsigned int sel)
	{
		wait();
		en_n = en; 
		dataIn = data; 
		selIn = sel;
	}

	void gen_input()
	{
		writeData(1, 200, 7);
		writeData(1, 200, 7);
		writeData(1, 200, 7);
		
		writeData(0, 200, 0);
		writeData(0, 200, 1);
		writeData(0, 200, 2);
		writeData(0, 200, 3);
		writeData(0, 200, 4);
		writeData(0, 200, 5);
		writeData(0, 200, 6);
		writeData(0, 200, 7);
		
		writeData(1, 200, 4);
		writeData(1, 200, 5);
		writeData(1, 200, 6);
		writeData(1, 200, 7);
	}

	void display_variable()
	{
		cout << "en_n = " << en_n << ", dataIn = " << dataIn << ", selIn = " << selIn << ", dataOut = " << dataOut
			<< ", flag = " << flag << endl;
	}
	
	SC_CTOR(tb)
	{
		SC_CTHREAD(gen_input, clk.pos());
		SC_METHOD(display_variable);
		sensitive << flag << dataOut << en_n << dataIn << selIn;
		dont_initialize();
	}

};

#endif
