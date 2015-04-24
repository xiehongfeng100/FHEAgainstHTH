#include "mux_8_1.h"
#include <math.h>

vector<int> int2bin(int num)
{
	vector<int> bin;
	while(true)
	{
		bin.push_back(num % 2);
		num /= 2;
		if(num == 0)
			break;
	}

	return bin;
}

int bin2int(vector<int> bin)
{
	int sz = bin.size();
	int sum = 0;
	for(int i = sz - 1; i > -1; i--)
	{
		sum += bin[i] * pow(2, i);
	}
	
	return sum;
}


vector<LWE::CipherText> enc(vector<int> data_8, LWE::SecretKey LWEsk)
{
	int sz = 8;
	vector<LWE::CipherText> cipher_8;
	cipher_8.resize(sz);
	// Encrypt every bit of inputs
	for(int i = 0; i < sz; i++)
	{
		LWE::Encrypt(&cipher_8[i], LWEsk, 1 - data_8[i]);
	}

	return cipher_8;
}

int dec(LWE::CipherText cipher, LWE::SecretKey LWEsk)
{
	int data;	
	data = LWE::Decrypt(LWEsk, cipher);
	return data;
}

LWE::CipherText mux_8_1(vector<LWE::CipherText> cipher_8, vector<int> sel_3, int en_n, LWE::SecretKey LWEsk, FHEW::EvalKey Ek)
{

	LWE::CipherText cipherEva;
	if(!en_n)
	{
		// Evaluation
		int pos = bin2int(sel_3);
		FHEW::HomNAND(&cipherEva, Ek, cipher_8[pos], cipher_8[pos]);
	}
	else
	{
		LWE::CipherText cipherOfZero;
		// Encrypt zero
		int data = 0;
		LWE::Encrypt(&cipherOfZero, LWEsk, 1 - data);
		FHEW::HomNAND(&cipherEva, Ek, cipherOfZero, cipherOfZero);
	}

	return cipherEva;
}

