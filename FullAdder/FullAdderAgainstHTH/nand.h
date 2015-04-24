#ifndef NAND_H
#define NAND_H

#include <systemc.h>
#include <math.h>

#include "LWE.h"
#include "FHEW.h"
#include "distrib.h"


  int v1,v2,sv1 = 2,sv2 = 2;
  LWE::CipherText se1, se2, e1, e2, e12;

  for (int i = 1; i <= 3*count; ++i) {

    if (i % 3){
      v1 = rand()%2;  
      v2 = rand()%2;
      LWE::Encrypt(&e1, LWEsk, v1);
      LWE::Encrypt(&e2, LWEsk, v2);
    }
    else { 
      v1 = sv1;
      v2 = sv2;
      e1 = se1;
      e2 = se2;
    }

SC_MODULE(nand)
{
	sc_in<bool> A;
	sc_in<bool> B;
	sc_out<bool> F;

	void do_nand()
	{
		F = !(A & B);
	}


	SC_CTOR(nand)
	{
		SC_METHOD(do_nand);
		sensitive << A << B;
	}

};

#endif
