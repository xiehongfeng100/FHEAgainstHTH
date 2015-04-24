#ifndef FULLADDER_H
#define FULLADDER_H

#include <iostream>
#include <vector>
#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"
using namespace std;

vector<int> int2bin(int num);
int bin2int(vector<int> bin);
vector<int> fulladder(vector<int> A, vector<int> B, int C, LWE::SecretKey LWEsk, FHEW::EvalKey Ek);

#endif
