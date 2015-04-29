#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"
using namespace std;

const int ENABLESIZE = 1;
const int INPUTSIZE = 8;
const int OUTPUTSIZE = 1;
const int SELECTSIZE = 3;


// FHE -------------------------------------

LWE::SecretKey LWEsk;
FHEW::EvalKey Ek;

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

LWE::CipherText encEN(int en_n, LWE::SecretKey LWEsk)
{
	LWE::CipherText cipherEN;
	en_n = 1 - en_n;
	LWE::Encrypt(&cipherEN, LWEsk, 1 - en_n); 
	return cipherEN;
}

vector<LWE::CipherText> encData(vector<int> data_8, LWE::SecretKey LWEsk)
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

LWE::CipherText mux81(vector<LWE::CipherText> cipher_8, vector<int> sel_3, int en_n, LWE::CipherText cipherEN, LWE::SecretKey LWEsk, FHEW::EvalKey Ek)
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
		// -- codes commented below is to simulate attack on enable signal 'en_n' ----------------
		// int pos = bin2int(sel_3);
		// if(pos == 3 || pos == 6)
		// {
		//		LWE::CipherText cipherOfOne;
		//		int data = 1;
		//		LWE::Encrypt(&cipherOfOne, LWEsk, 1 - data);
		//		FHEW::HomNAND(&cipherEva, Ek, cipherOfOne, cipherOfOne);
		// }
		// else
		// {
			// HomNAND of cipher of en_n when it equals 1
			FHEW::HomNAND(&cipherEva, Ek, cipherEN, cipherEN);
		// }
	}
	return cipherEva;
}

#endif
