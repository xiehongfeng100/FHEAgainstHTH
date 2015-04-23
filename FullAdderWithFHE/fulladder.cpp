#include "fulladder.h"
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

vector<int> fulladder(vector<int> A, vector<int> B, int C, LWE::SecretKey LWEsk, FHEW::EvalKey Ek)
{
	vector<int> product, carry;
	vector<LWE::CipherText> cipherOfA, rcipherOfA, cipherOfB, rcipherOfB, cipherOfC;
	vector<LWE::CipherText> cipherEvaOfAB, rcipherEvaOfAB, cipherEvaOfC;
	
	// resizing 
	int sz = max(A.size(), B.size());
	A.resize(sz);
	B.resize(sz);
	
	cipherOfA.resize(sz);
	rcipherOfA.resize(sz);
	cipherOfB.resize(sz);
	rcipherOfB.resize(sz);
	
	cipherEvaOfAB.resize(sz);
	rcipherEvaOfAB.resize(sz);

	cipherOfC.resize(sz+1);
	cipherEvaOfC.resize(sz+1);

	product.resize(sz+1);
	carry.resize(sz+1);

	// Encryption
	LWE::Encrypt(&cipherOfC[0], LWEsk, 1 - C);
	for(int i = 0; i < sz; i++)
	{
		// Encrypt carry
		LWE::Encrypt(&cipherOfC[i+1], LWEsk, 1 - A[i] * B[i]);
		// Encrypt A & B
		LWE::Encrypt(&cipherOfA[i], LWEsk, A[i]);
		LWE::Encrypt(&cipherOfB[i], LWEsk, B[i]);
		// Encrypt ~A & ~B
		LWE::Encrypt(&rcipherOfA[i], LWEsk, 1 - A[i]);
		LWE::Encrypt(&rcipherOfB[i], LWEsk, 1 - B[i]);
	}
	
	// Evaluation
	FHEW::HomNAND(&cipherEvaOfC[0], Ek, cipherOfC[0], cipherOfC[0]);
	for(int i = 0; i < sz; i++)
	{
		// Evaluate the cipher of carry
		FHEW::HomNAND(&cipherEvaOfC[i+1], Ek, cipherOfC[i+1], cipherOfC[i+1]);
		// Evaluate the product of cipher of A & B
		FHEW::HomNAND(&cipherEvaOfAB[i], Ek, cipherOfA[i], cipherOfB[i]);
		// Evaluate the product of cipher of A & B
		FHEW::HomNAND(&rcipherEvaOfAB[i], Ek, rcipherOfA[i], rcipherOfB[i]);
	}
	
	// Decryption
	carry[0] = LWE::Decrypt(LWEsk, cipherEvaOfC[0]);
	for(int i = 0; i < sz; i++)
	{
		product[i] = LWE::Decrypt(LWEsk, cipherEvaOfAB[i]) * LWE::Decrypt(LWEsk, rcipherEvaOfAB[i]);
		carry[i+1] = LWE::Decrypt(LWEsk, cipherEvaOfC[i+1]);
	}

	cout << "Product: " << endl;
	for(int i = 0; i < sz + 1; i++)
	{
		cout << product[i] << " ";
	}
	cout << endl;

	cout << "Carry: " << endl;
	for(int i = 0; i < sz + 1; i++)
	{
		cout << carry[i] << " ";
	}	
	cout << endl;

	// Sum up	
	vector<int> fulladd;
	fulladd.resize(sz + 1);
	int c = 0;
	for(int i = 0; i < sz+1; i++)
	{
		int temp = c + product[i] + carry[i];
		if(temp < 2)
		{
			fulladd[i] = temp;
			c = 0;
		}
		else if(temp == 2)
		{
			fulladd[i] = 0;
			c = 1;
		}
		else
		{
			fulladd[i] = 1;
			c = 1;
		}
	}

	return fulladd;
}

