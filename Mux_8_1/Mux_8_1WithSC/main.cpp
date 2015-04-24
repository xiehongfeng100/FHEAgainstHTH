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
	sc_clock clk("Clk", 20, SC_NS);
	
	mux_8_1 MUX_8_1("MUX_8_1");
	MUX_8_1.en_n(en_n);
	MUX_8_1.dataIn(dataIn);
	MUX_8_1.selIn(selIn);
	MUX_8_1.dataOut(dataOut);

	tb TB("TB");
	TB.clk(clk);
	TB.en_n(en_n);
	TB.dataIn(dataIn);
	TB.selIn(selIn);
	TB.dataOut(dataOut);

	// create trace file
	sc_trace_file *tf = sc_create_vcd_trace_file("Mux_8_1");
	sc_trace(tf, MUX_8_1.en_n, "en_n");
	sc_trace(tf, MUX_8_1.dataIn, "dataIn");
	sc_trace(tf, MUX_8_1.selIn, "selIn");
	sc_trace(tf, MUX_8_1.dataOut, "dataOut");
	sc_trace(tf, TB.clk, "CLK");
	sc_start(200, SC_NS);
	sc_close_vcd_trace_file(tf);

	return 0;
}
