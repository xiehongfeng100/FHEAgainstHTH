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
	
	void do_mux()
	{
		if(en_n.read() == 0)
		{
			switch(selIn.read())
			{
				case 7:
						dataOut.write((0x80 & dataIn.read()) >> 7);
						break;
				case 6:
						dataOut.write((0x40 & dataIn.read()) >> 6);
						break;
				case 5:
						dataOut.write((0x20 & dataIn.read()) >> 5);
						break;
				case 4:
						dataOut.write((0x10 & dataIn.read()) >> 4);
						break;
				case 3:
						dataOut.write((0x8 & dataIn.read()) >> 3);
						break;
				case 2:
						dataOut.write((0x4 & dataIn.read()) >> 2);
						break;
				case 1:
						dataOut.write((0x2 & dataIn.read()) >> 1);
						break;
				case 0:
						dataOut.write(0x1 & dataIn.read() >> 0);
						break;
				default:
						dataOut.write(0x0);
			}	
		}
		else
		{
			cout << "en_n = 0!" << endl;
			dataOut.write(0x0);
		}
	}

	SC_CTOR(mux_8_1)
	{
		SC_METHOD(do_mux);
		sensitive << en_n << dataIn << selIn;
	}

};

#endif
