#include <systemc.h>
#include "nand.h"
#include "tb.h"

int sc_main(int, char **)
{
	sc_signal<bool> a, b, f;
	sc_clock clk("Clk", 20, SC_NS);	// 时钟周期为 20ns
	
	// 分别定义模块 NAND 和 TB 的实例，并通过局部变量（如 a、b）将这两个实例连接起来
	nand NAND("NAND");
	NAND.A(a);
	NAND.B(b);
	NAND.F(f);

	tb TB("TB");
	TB.clk(clk);
	TB.a(a);
	TB.b(b);
	TB.f(f);

	// 生成仿真结果波形文件
	sc_trace_file *tf = sc_create_vcd_trace_file("NAND");
	sc_trace(tf, NAND.A, "A");
	sc_trace(tf, NAND.B, "B");
	sc_trace(tf, NAND.F, "F");
	sc_trace(tf, TB.clk, "CLK");
	sc_start(200, SC_NS);	// 仿真时长 200ns
	sc_close_vcd_trace_file(tf);

	return 0;
}
