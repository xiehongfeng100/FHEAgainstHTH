#ifndef COMMON_H
#define COMMON_H

// 全同态加密库 FHEW 的头文件
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"

LWE::SecretKey LWEsk;	// 密钥（加解密共用）
FHEW::EvalKey Ek;		// 密文计算公钥

// 加密函数
LWE::CipherText enc(int plain, LWE::SecretKey LWEsk)
{
	LWE::CipherText cipher;
	LWE::Encrypt(&cipher, LWEsk, plain); 
	return cipher;
}

// 解密函数
int dec(LWE::CipherText cipherF, LWE::SecretKey LWEsk)
{
	int plain;	
	plain = LWE::Decrypt(LWEsk, cipherF);
	return plain;
}

// 密文计算函数
LWE::CipherText nandInCipher(LWE::CipherText cipherA, LWE::CipherText cipherB, FHEW::EvalKey Ek)
{
	LWE::CipherText cipherF;
	FHEW::HomNAND(&cipherF, Ek, cipherA, cipherB);
	return cipherF;
}

#endif
