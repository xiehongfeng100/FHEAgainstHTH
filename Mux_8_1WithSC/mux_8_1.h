#ifndef MUX_8_1_H
#define MUX_8_1_H

#include <systemc.h>
#include <math.h>
#include "common.h"

SC_MODULE(mux_8_1)
{
	sc_in<sc_uint<INPUTSIZE> > dataIn;
	sc_in<sc_uint<SELECTSIZE> > selIn;
	sc_out<sc_uint<OUTPUTSIZE> > dataOut;
	
	void do_mux()
	{

		switch(selIn.read())
		{
			case 7:
					dataOut.write(1);
					//dataOut.write((0x80 & dataIn.read()) >> 7);
			case 6:
					dataOut.write((0x40 & dataIn.read()) >> 6);
			case 5:
					dataOut.write((0x20 & dataIn.read()) >> 5);
			case 4:
					dataOut.write((0x10 & dataIn.read()) >> 4);
			case 3:
					dataOut.write((0x8 & dataIn.read()) >> 3);
			case 2:
					dataOut.write((0x4 & dataIn.read()) >> 2);
			case 1:
					dataOut.write((0x2 & dataIn.read()) >> 1);
			case 0:
					dataOut.write(0x1 & dataIn.read());
			default:
					dataOut.write(0x0);

		}	
	//	if(selIn[2])
	//	{
	//		if(selIn[1])
	//		{
	//			if(selIn[0])	// selIn = 0b111
	//				dataOut.write((0x80 & dataIn.read()) >> 7);
	//			else			// selIn = 0b110
	//				dataOut.write((0x40 & dataIn.read()) >> 6);
	//		}
	//		else
	//		{
	//			if(selIn[0])	// selIn = 0b101
	//				dataOut.write((0x20 & dataIn.read()) >> 5);
	//			else			// selIn = 0b100
	//				dataOut.write((0x10 & dataIn.read()) >> 4);
	//		}

	//	}
	//	else
	//	{
	//		if(selIn[1])
	//		{
	//			if(selIn[0])	// selIn = 0b011
	//				dataOut.write((0x8 & dataIn.read()) >> 3);
	//			else			// selIn = 0b010
	//				dataOut.write((0x4 & dataIn.read()) >> 2);
	//		}
	//		else
	//		{
	//			if(selIn[0])	// selIn = 0b001
	//				dataOut.write((0x2 & dataIn.read()) >> 1);
	//			else			// selIn = 0b000
	//				dataOut.write(0x1 & dataIn.read());
	//		}


	//	}
	}

	SC_CTOR(mux_8_1)
	{
		SC_METHOD(do_mux);
		sensitive << dataIn << selIn;
	}

};

//int bin2int(vector<int> bin)
//{
//	int sz = bin.size();
//	int sum = 0;
//	for(int i = sz - 1; i > -1; i--)
//	{
//		sum += bin[i] * pow(2, i);
//	}
//	
//	return sum;
//}

#endif
