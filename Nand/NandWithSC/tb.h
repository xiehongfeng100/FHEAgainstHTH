#ifndef TB_H
#define TB_H

#include <systemc.h>

// 测试平台（Testbench）
SC_MODULE(tb)
{
	sc_out<bool> a, b;
	sc_in<bool> f;
	sc_in_clk clk;

	// 输入激励
	void gen_input()
	{
		wait(); a = 0; b = 0;
		wait(); a = 0; b = 1;
		wait(); a = 1; b = 0;
		wait(); a = 1; b = 1;
		wait(); a = 0; b = 0;
		wait(); a = 0; b = 0;
	}

	void display_variable()
	{
		cout << "a = " << a << ", b = " << b << ", f = " << f << endl;
	}
	
	SC_CTOR(tb)
	{
		// SC_CTHREAD 和 SC_METHOD 基本类似，只是它可以使用 wait() 函数
		// 下句中的 clk.pos() 指明了电路在时钟上升沿触发
		SC_CTHREAD(gen_input, clk.pos());
		SC_METHOD(display_variable);
		sensitive << f << a << b;
		dont_initialize();
	}

};

#endif
