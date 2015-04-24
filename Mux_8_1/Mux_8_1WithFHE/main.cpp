#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"
#include "mux_8_1.h"

using namespace std;

void help(char* cmd) {
  cerr << "\nusage: " << cmd << " n\n\n" 
  << "  Generate a secret key sk and evaluation key ek, and repeat the following test n times:\n"
  << "   - generate random bits b1,b2,b3,b4\n"
  << "   - compute ciphertexts c1, c2, c3 and c4 encrypting b1, b2, b3 and b4  under sk\n"
  << "   - homomorphically compute the encrypted (c1 NAND c2) NAND (c3 NAND c4) \n"
  << "   - decrypt all the intermediate results and check correctness \n"
  << "\n If any of the tests fails, print ERROR and stop immediately.\n\n";
  exit(0);
}

void output(int& elem)
{
	cout << elem << " ";
}

int main() 
{
	cerr << "Setting up FHEW \n";
	FHEW::Setup();
	cerr << "Generating secret key ... ";
	LWE::SecretKey LWEsk;
	LWE::KeyGen(LWEsk);
	cerr << " Done.\n";
	cerr << "Generating evaluation key ... this may take a while ... ";
	FHEW::EvalKey Ek;
	FHEW::KeyGen(&Ek, LWEsk);
	cerr << " Done.\n\n";
		
	int dataIn = 100;
	vector<int> data_8;
	data_8.resize(8);
	data_8 = int2bin(dataIn);

	cout << "dataIn: ";
	cout << dataIn;
	cout << endl;

	cout << "data_8: ";
	for_each(data_8.begin(), data_8.end(), output);
	cout << endl;
	
	vector<LWE::CipherText> cipher_8;
	cipher_8 = enc(data_8, LWEsk);

	int sz = 20;
	for(int i = 0; i < sz; i++)
	{
		if(i < 8)
		{
			int en_n = 0;
			vector<int> sel_3 = int2bin(i);
			LWE::CipherText cipherOut;
			cipherOut = mux_8_1(cipher_8, sel_3, en_n, LWEsk, Ek);
			int out;	
			out = dec(cipherOut, LWEsk);
			cout << "en_n = 0, and "<< "select the " << i << "th dataIn!" << endl;
			cout << "    dataOut is " << out << endl;
		}
		else
		{
			int en_n = 1;
			vector<int> sel_3 = int2bin(i);
			LWE::CipherText cipherOut;
			cipherOut = mux_8_1(cipher_8, sel_3, en_n, LWEsk, Ek);
			int out;	
			out = dec(cipherOut, LWEsk);
			cout << "en_n = 1, and "<< "select the " << i << "th dataIn!" << endl;
			cout << "    dataOut is " << out << endl;
		}
	}
}


