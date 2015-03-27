#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"
#include "fulladder.h"

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

int main() {

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
		
  vector<int> A = int2bin(100);
  vector<int> B = int2bin(7);
  int C = 0;

  cout << "A: ";
  for_each(A.begin(), A.end(), output);
  cout << endl;
  cout << "B: ";
  for_each(B.begin(), B.end(), output);
  cout << endl;
  cout << "C: " << C;
  cout << endl;
  
  vector<int> fulladdInBin = fulladder(A, B, C, LWEsk, EK);
  int fulladdInInt = bin2int(fulladdInBin);
  cout << "Full add(in int): " << fulladdInInt << endl;

}


