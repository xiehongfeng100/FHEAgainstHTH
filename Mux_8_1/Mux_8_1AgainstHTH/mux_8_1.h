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
		// Read dataIn
		vector<int> data_8;
		data_8.resize(8);
		data_8 = int2bin(dataIn.read());

		// Encrypt dataIn
		vector<LWE::CipherText> cipher_8;
		cipher_8 = enc(data_8, LWEsk);

		// Read selIn
		vector<int> sel_3 = int2bin(selIn.read());
	
		// Select one
		unsigned int en = en_n.read();
		LWE::CipherText cipherOut;
		cipherOut = mux81(cipher_8, sel_3, en, LWEsk, Ek);
		
		// Decrypt dataOut
		int out;	
		out = dec(cipherOut, LWEsk);
		dataOut.write(out);

	}

	SC_CTOR(mux_8_1)
	{
		SC_METHOD(do_mux);
		sensitive << dataIn << selIn;
	}

};

#endif
