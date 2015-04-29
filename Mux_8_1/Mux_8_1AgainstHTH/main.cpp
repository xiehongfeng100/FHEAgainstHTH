#include <systemc.h>
#include "common.h"
#include "mux_8_1.h"
#include "tb.h"

int sc_main(int, char **)
{
	sc_signal<sc_uint<ENABLESIZE> > en_n;
	sc_signal<sc_uint<INPUTSIZE> > dataIn;
	sc_signal<sc_uint<SELECTSIZE> > selIn;
	sc_signal<sc_uint<OUTPUTSIZE> > dataOut;
	sc_signal<sc_uint<OUTPUTSIZE> > flag;
	sc_clock clk("Clk", 20, SC_NS);
	
	// Connect modules ------------------------------------------
	mux_8_1 MUX_8_1("MUX_8_1");
	MUX_8_1.en_n(en_n);
	MUX_8_1.dataIn(dataIn);
	MUX_8_1.selIn(selIn);
	MUX_8_1.dataOut(dataOut);
	MUX_8_1.flag(flag);

	tb TB("TB");
	TB.clk(clk);
	TB.en_n(en_n);
	TB.dataIn(dataIn);
	TB.selIn(selIn);
	TB.dataOut(dataOut);
	TB.flag(flag);

	// Initialize keys ------------------------------------------
	cout << "Setting up FHEW" << endl;
	FHEW::Setup();
	cout << "Generating secret key ... " << endl;
	//LWE::SecretKey LWEsk;
	LWE::KeyGen(LWEsk);
	cout << "Done." << endl;
	cout << "Generating evaluation key ... this may take a while ... " << endl;
	//FHEW::EvalKey Ek;
	FHEW::KeyGen(&Ek, LWEsk);
	cout << "Done." << endl << endl;

	// Create trace files ----------------------------------------
	sc_trace_file *tf = sc_create_vcd_trace_file("Mux_8_1");
	sc_trace(tf, MUX_8_1.en_n, "en_n");
	sc_trace(tf, MUX_8_1.dataIn, "dataIn");
	sc_trace(tf, MUX_8_1.selIn, "selIn");
	sc_trace(tf, MUX_8_1.dataOut, "dataOut");
	sc_trace(tf, MUX_8_1.flag, "flag");
	sc_trace(tf, TB.clk, "CLK");
	sc_start(400, SC_NS);
	sc_close_vcd_trace_file(tf);

	return 0;
}

