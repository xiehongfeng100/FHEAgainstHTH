#include <systemc.h>
#include "nand.h"
#include "tb.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"
#include "mux_8_1.h"

using namespace std;

void output(int& elem)
{
	cout << elem << " ";
}

int sc_main(int, char **)
{
	sc_signal<bool> a, b, f;
	sc_clock clk("Clk", 20, SC_NS);
	
	nand NAND("NAND");
	NAND.A(a);
	NAND.B(b);
	NAND.F(f);

	tb TB("TB");
	TB.clk(clk);
	TB.a(a);
	TB.b(b);
	TB.f(f);

	// create trace file
	sc_trace_file *tf = sc_create_vcd_trace_file("NAND");
	sc_trace(tf, NAND.A, "A");
	sc_trace(tf, NAND.B, "B");
	sc_trace(tf, NAND.F, "F");
	sc_trace(tf, TB.clk, "CLK");
	sc_start(200, SC_NS);
	sc_close_vcd_trace_file(tf);

	cerr << "Setting up FHEW \n";
	FHEW::Setup();
	cerr << "Generating secret key ... ";
	LWE::SecretKey LWEsk;
	LWE::KeyGen(LWEsk);
	cerr << " Done.\n";
	cerr << "Generating evaluation key ... this may take a while ... ";
	FHEW::EvalKey Ek;
	FHEW::KeyGen(&Ek, LWEsk);
	cerr << " Done.\n\n";
		
	int dataIn = 100;
	vector<int> data_8;
	data_8.resize(8);
	data_8 = int2bin(dataIn);

	cout << "dataIn: ";
	cout << dataIn;
	cout << endl;

	cout << "data_8: ";
	for_each(data_8.begin(), data_8.end(), output);
	cout << endl;
	
	vector<LWE::CipherText> cipher_8;
	cipher_8 = enc(data_8, LWEsk);

	int sz = 10;
	for(int i = 0; i < sz; i++)
	{
		if(i < 8)
		{
			int en_n = 0;
			vector<int> sel_3 = int2bin(i);
			LWE::CipherText cipherOut;
			cipherOut = mux_8_1(cipher_8, sel_3, en_n, LWEsk, Ek);
			int out;	
			out = dec(cipherOut, LWEsk);
			cout << "en_n = 0, and "<< "select the " << i << "th dataIn!" << endl;
			cout << "    dataOut is " << out << endl;
		}
		else
		{
			int en_n = 1;
			vector<int> sel_3 = int2bin(i);
			LWE::CipherText cipherOut;
			cipherOut = mux_8_1(cipher_8, sel_3, en_n, LWEsk, Ek);
			int out;	
			out = dec(cipherOut, LWEsk);
			cout << "en_n = 1, and "<< "select the " << i << "th dataIn!" << endl;
			cout << "    dataOut is " << out << endl;
		}
	}

    return 0;
}


