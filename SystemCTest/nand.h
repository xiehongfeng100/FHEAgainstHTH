#ifndef NAND_H
#define NAND_H

#include <systemc.h>	// 包含 SystemC 头文件
#include <math.h>

// 定义一个模块 nand
SC_MODULE(nand)
{
	// 定义该模块输入输出端口
	sc_in<bool> A;
	sc_in<bool> B;
	sc_out<bool> F;

	// 描述电路实际功能
	void do_nand()
	{
		F = !(A & B);
	}

	// 描述该模块行为的进程模型
	SC_CTOR(nand)	
	{
		SC_METHOD(do_nand);	// 描述电路组合逻辑，当敏感信号变化时被触发
		sensitive << A << B;// 敏感信号列表
	}

};

#endif
