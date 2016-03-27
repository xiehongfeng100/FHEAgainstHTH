#ifndef NAND_H
#define NAND_H

#include <systemc.h>
#include <math.h>
#include "common.h"	// 变量及函数声明或定义

// 定义一个模块 nand
SC_MODULE(nand)
{
	// 定义该模块（密文）输入输出端口
	// 在这里假设用32位已足以表示输入和输出密文
	sc_in<sc_uint<32> > A;
	sc_in<sc_uint<32> > B;
	sc_in<sc_uint<32> > F;

	// 对输入的密文进行计算，并将最终结果输出
	void do_nand()
	{
		int cipherA = A.read();
		int cipherB = B.read();
		int cipherF = nandInCipher(cipherA, cipherB, Ek);
		F.write(cipherF);
	}

	// 描述该模块行为的进程模型
	SC_CTOR(nand)
	{
		SC_METHOD(do_nand);
		sensitive << A << B;
	}

};

#endif
