#include <systemc.h>
#include "common.h"
#include "fulladder.h"
#include "tb.h"

using namespace std;

void output(int& elem)
{
	cout << elem << " ";
}

int sc_main(int, char **)
{
    sc_signal<sc_uint<INPUTSIZE> > A_sc;
    sc_signal<sc_uint<INPUTSIZE> > B_sc;
    sc_signal<sc_uint<CARRYSIZE> > Cin_sc;
    sc_signal<sc_uint<OUTPUTSIZE> > S_sc;
    sc_signal<sc_uint<CARRYSIZE> > Cout_sc;
    sc_clock clk("Clk", 20, SC_NS);

    // Connect modules
    fulladder FullAdder("FullAdder");
    FullAdder.A_sc(A_sc);
    FullAdder.B_sc(B_sc);
    FullAdder.Cin_sc(Cin_sc);
    FullAdder.S_sc(S_sc);
    FullAdder.Cout_sc(Cout_sc);

    tb TB("TB");
    TB.clk(clk);
    TB.A_sc(A_sc); 
    TB.B_sc(B_sc); 
    TB.Cin_sc(Cin_sc);
    TB.S_sc(S_sc);
    TB.Cout_sc(Cout_sc);

    // Initialize keys
    cerr << "Setting up FHEW \n";
    FHEW::Setup();
    cerr << "Generating secret key ... ";
    // LWE::SecretKey LWEsk;
    LWE::KeyGen(LWEsk);
    cerr << " Done.\n";
    cerr << "Generating evaluation key ... this may take a while ... ";
    // FHEW::EvalKey EK;
    FHEW::KeyGen(&Ek, LWEsk);
    cerr << " Done.\n\n";
      	
    // create trace file
    sc_trace_file *tf = sc_create_vcd_trace_file("FullAdder"); 
    sc_trace(tf, FullAdder.A_sc, "A"); 
    sc_trace(tf, FullAdder.B_sc, "B");
    sc_trace(tf, FullAdder.Cin_sc, "Cin");
    sc_trace(tf, FullAdder.S_sc, "S");
    sc_trace(tf, FullAdder.Cout_sc, "Cout");
    sc_trace(tf, TB.clk, "CLK");
    sc_start(400, SC_NS);
    sc_close_vcd_trace_file(tf);
    
    return 0;
}
