#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"

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

int main(/* int argc, char *argv[] */) {
 // if (argc != 2) help(argv[0]);
 // int count = atoi(argv[1]); 
 // int count = 1;	

  cerr << "Setting up FHEW \n";
  FHEW::Setup();
  cerr << "Generating secret key ... ";
  LWE::SecretKey LWEsk;
  LWE::KeyGen(LWEsk);
  cerr << " Done.\n";
  cerr << "Generating evaluation key ... this may take a while ... ";
  FHEW::EvalKey EK;
  FHEW::KeyGen(&EK, LWEsk);
  cerr << " Done.\n\n";
 // cerr << "Testing homomorphic NAND " << count << " times.\n"; 
 // cerr << "Circuit shape : (a NAND b) NAND (c NAND d)\n\n";

 // int v1,v2;
 // LWE::CipherText e1, e2, e12;

 // v1 = 1;  
 // v2 = 0;
 // LWE::Encrypt(&e1, LWEsk, v1);
 // LWE::Encrypt(&e2, LWEsk, v2);
 //    
 // cerr << "Enc(" << v1 << ")  NAND  Enc(" << v2 << ")  =  ";
 // 
 // FHEW::HomNAND(&e12, EK, e1, e2);
 // int v12 = LWE::Decrypt(LWEsk, e12);

 // cerr << "Enc(" << v12 << ")";
 // cerr << endl;

 // if (1 - v1*v2 != v12) 
 // { 
 //     cerr << "ERROR" << "\n"; 
 //     exit(1); 
 // }

 // cerr << "\nPassed all tests!\n\n";

	int carryin = 0;
	vector<int> bits1, bits2, product, carry;
	vector<LWE::CipherText> cipher11, cipher12, cipher21, cipher22,  ccarry;
	vector<LWE::CipherText> cipher_ek1, cipher_ek2, ccarry_ek;
	
	// initialization
	bits1.push_back(1);
	bits1.push_back(0);
	bits1.push_back(1);
	bits2.push_back(1);
	bits2.push_back(1);

	carryin = 1;
	
	// resizeing
	int sz = max(bits1.size(), bits2.size());
	bits1.resize(sz);
	bits2.resize(sz);

	cipher11.resize(sz);
	cipher12.resize(sz);
	cipher21.resize(sz);
	cipher22.resize(sz);
	cipher_ek1.resize(sz);
	cipher_ek2.resize(sz);
	
	ccarry.resize(sz+1);	// to include carryin
	ccarry_ek.resize(sz+1);

	product.resize(sz);
	carry.resize(sz+1);

	// Encrypt
	LWE::Encrypt(&ccarry[0], LWEsk, 1 - carryin);
	for(int i = 0; i < sz; i++)
	{
		// encrypt carry
		LWE::Encrypt(&ccarry[i+1], LWEsk, 1 - bits1[i] * bits2[i]);
		// encrypt bits
		LWE::Encrypt(&cipher11[i], LWEsk, bits1[i]);
		LWE::Encrypt(&cipher21[i], LWEsk, bits2[i]);

		LWE::Encrypt(&cipher12[i], LWEsk, 1 - bits1[i]);
		LWE::Encrypt(&cipher22[i], LWEsk, 1 - bits2[i]);
	}

	// Calculate
	FHEW::HomNAND(&ccarry_ek[0], EK, ccarry[0], ccarry[0]);
	for(int i = 0; i < sz; i++)
	{
		FHEW::HomNAND(&ccarry_ek[i+1], EK, ccarry[i+1], ccarry[i+1]);
		FHEW::HomNAND(&cipher_ek1[i], EK, cipher11[i], cipher21[i]);
		FHEW::HomNAND(&cipher_ek2[i], EK, cipher12[i], cipher22[i]);
	}

	// Decrypt
	carry[0] = LWE::Decrypt(LWEsk, ccarry_ek[0]);
	cout << "carrin == " << carry[0] << endl;
	for(int i = 0; i < sz; i++)
	{
		product[i] = LWE::Decrypt(LWEsk, cipher_ek1[i]) * LWE::Decrypt(LWEsk, cipher_ek2[i]);
		carry[i+1] = LWE::Decrypt(LWEsk, ccarry_ek[i+1]);
		cout << product[i] << " " << carry[i+1] << endl;
	}
	
}


