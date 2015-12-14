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

const int INPUTSIZE = 8;
const int OUTPUTSIZE = 8;
const int CARRYSIZE = 1;

// FHE
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

void enc(vector<int> A, vector<int> B, int Cin, LWE::SecretKey LWEsk,
		vector<LWE::CipherText>& cipherOfA, vector<LWE::CipherText>& rcipherOfA,
		vector<LWE::CipherText>& cipherOfB, vector<LWE::CipherText>& rcipherOfB,
		vector<LWE::CipherText>& cipherOfC)
{
	// resizing
	// int sz = max(A.size(), B.size());
	A.resize(INPUTSIZE);
	B.resize(INPUTSIZE);
	
	cipherOfA.resize(INPUTSIZE);
	rcipherOfA.resize(INPUTSIZE);
	cipherOfB.resize(INPUTSIZE);
	rcipherOfB.resize(INPUTSIZE);

	cipherOfC.resize(INPUTSIZE);

	// Encryption
	LWE::Encrypt(&cipherOfC[0], LWEsk, 1 - Cin);
	for(int i = 0; i < INPUTSIZE; i++)
	{
		// Encrypt carry
		LWE::Encrypt(&cipherOfC[i + 1], LWEsk, 1 - A[i] * B[i]);
		// Encrypt A and B
		LWE::Encrypt(&cipherOfA[i], LWEsk, A[i]);
		LWE::Encrypt(&cipherOfB[i], LWEsk, B[i]);
		// Encrypt ~A and ~B
		LWE::Encrypt(&rcipherOfA[i], LWEsk, 1 - A[i]);
		LWE::Encrypt(&rcipherOfB[i], LWEsk, 1 - B[i]);
	}
}

void eva(FHEW::EvalKey Ek,
		vector<LWE::CipherText>& cipherOfA, vector<LWE::CipherText>& rcipherOfA,
		vector<LWE::CipherText>& cipherOfB, vector<LWE::CipherText>& rcipherOfB,
		vector<LWE::CipherText>& cipherOfC,
		vector<LWE::CipherText>& cipherEvaOfAB, vector<LWE::CipherText>& rcipherEvaOfAB,
		vector<LWE::CipherText>& cipherEvaOfC)
{
	// Resizing
	cipherEvaOfAB.resize(INPUTSIZE); 
	rcipherEvaOfAB.resize(INPUTSIZE); 
	cipherEvaOfC.resize(INPUTSIZE + 1);
	// Evaluation
	FHEW::HomNAND(&cipherEvaOfC[0], Ek, cipherOfC[0], cipherOfC[0]);
	for(int i = 0; i < INPUTSIZE; i++)
	{
		// Evaluate the cipher of carry
		FHEW::HomNAND(&cipherEvaOfC[i + 1], Ek, cipherOfC[i + 1], cipherOfC[i + 1]);
		// Evaluate the product of cipher of cipher of A & B
		FHEW::HomNAND(&cipherEvaOfAB[i], Ek, cipherOfA[i], cipherOfB[i]);
		// Evaluate the product of cipher of ~A & ~B
		FHEW::HomNAND(&rcipherEvaOfAB[i], Ek, rcipherOfA[i], rcipherOfB[i]);
	}
}


void dec(LWE::SecretKey LWEsk,
		vector<LWE::CipherText> cipherEvaOfAB, vector<LWE::CipherText> rcipherEvaOfAB,
		vector<LWE::CipherText> cipherEvaOfC,
		vector<int>& S, int& Cout)
{
	vector<int> product(INPUTSIZE + 1, 0), carry(INPUTSIZE + 1, 0);
	// Decryption
	carry[0] = LWE::Decrypt(LWEsk, cipherEvaOfC[0]);
	for(int i = 0; i < INPUTSIZE; i++)
	{
		product[i] = LWE::Decrypt(LWEsk, cipherEvaOfAB[i]) * 
			LWE::Decrypt(LWEsk, rcipherEvaOfAB[i]);
		carry[i + 1] = LWE::Decrypt(LWEsk, cipherEvaOfC[i + 1]);
	}

	// Sum up
	S.resize(INPUTSIZE + 1);
	int c = 0;
	for(int i = 0; i < INPUTSIZE + 1; i++)
	{
		int temp = c + product[i] + carry[i];
		if(temp < 2)
		{
			S[i] = temp;
			c = 0;
		}
		else if(temp == 2)
		{
			S[i] = 0;
			c = 1;
		}
		else
		{
			S[i] = 1;
			c = 1;
		}
	}

	Cout = S[INPUTSIZE];
	S.resize(INPUTSIZE);
}


#endif
