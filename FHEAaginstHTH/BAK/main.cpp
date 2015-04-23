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
#include "fulladder.h"

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
    FHEW::EvalKey EK;
    FHEW::KeyGen(&EK, LWEsk);
    cerr << " Done.\n\n";
      	
    vector<int> A = int2bin(100);
    vector<int> B = int2bin(7);
    int C = 0;

    cout << "A: ";
    for_each(A.begin(), A.end(), output);
    cout << endl;
    cout << "B: ";
    for_each(B.begin(), B.end(), output);
    cout << endl;
    cout << "C: " << C;
    cout << endl;
    
    vector<int> fulladdInBin = fulladder(A, B, C, LWEsk, EK);
    int fulladdInInt = bin2int(fulladdInBin);
    cout << "Full add(in int): " << fulladdInInt << endl;

    return 0;
}
