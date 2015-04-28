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
		// Read dataIn
		vector<int> data_8;
		data_8.resize(8);
		data_8 = int2bin(dataIn.read());

		// Encrypt dataIn
		vector<LWE::CipherText> cipher_8;
		cipher_8 = encData(data_8, LWEsk);
		
		// Encrypt en_n
		int en = en_n.read();
		LWE::CipherText cipherEN = encEN(en, LWEsk);

		// Read selIn
		vector<int> sel_3 = int2bin(selIn.read());
	
		// Select one
		LWE::CipherText cipherOut;
		cipherOut = mux81(cipher_8, sel_3, en, cipherEN, LWEsk, Ek);
		
		// Decrypt dataOut
		int out;	
		out = dec(cipherOut, LWEsk);
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
