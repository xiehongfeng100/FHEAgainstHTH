#ifndef COMMON_H
#define COMMON_H

// ȫ̬ͬ���ܿ� FHEW ��ͷ�ļ�
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"

LWE::SecretKey LWEsk;	// ��Կ���ӽ��ܹ��ã�
FHEW::EvalKey Ek;		// ���ļ��㹫Կ

// ���ܺ���
LWE::CipherText enc(int plain, LWE::SecretKey LWEsk)
{
	LWE::CipherText cipher;
	LWE::Encrypt(&cipher, LWEsk, plain); 
	return cipher;
}

// ���ܺ���
int dec(LWE::CipherText cipherF, LWE::SecretKey LWEsk)
{
	int plain;	
	plain = LWE::Decrypt(LWEsk, cipherF);
	return plain;
}

// ���ļ��㺯��
LWE::CipherText nandInCipher(LWE::CipherText cipherA, LWE::CipherText cipherB, FHEW::EvalKey Ek)
{
	LWE::CipherText cipherF;
	FHEW::HomNAND(&cipherF, Ek, cipherA, cipherB);
	return cipherF;
}

#endif
