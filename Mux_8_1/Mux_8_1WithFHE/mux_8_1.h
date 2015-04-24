#ifndef MUX_8_1_H
#define MUX_8_1_H

#include <iostream>
#include <vector>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"
using namespace std;

vector<int> int2bin(int num);
int bin2int(vector<int> bin);
vector<LWE::CipherText> enc(vector<int> data_8, LWE::SecretKey LWEsk);
int dec(LWE::CipherText cipher, LWE::SecretKey LWEsk);
LWE::CipherText mux_8_1(vector<LWE::CipherText> cipher_8, vector<int> sel_3, int en_n, LWE::SecretKey LWEsk, FHEW::EvalKey Ek);

#endif
