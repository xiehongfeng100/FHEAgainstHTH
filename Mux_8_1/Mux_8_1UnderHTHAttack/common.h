#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int ENABLESIZE = 1;
const int INPUTSIZE = 8;
const int OUTPUTSIZE = 1;
const int SELECTSIZE = 3;


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


#endif
