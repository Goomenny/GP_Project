#pragma once
#include "HarrixMathLibrary.h"
#include "TTree.h"
#include "DIFFEVO.h"
class TTest
{
public:
	void Calculate( TTree_symbolic &tree);

	double Get_reliability() { return reliability; };
	double Get_meanresult() { return meanresult; };

private:
	TDE optimizer;
	int runs = 100;
	double eps = 0.01;

	double reliability = 0;
	double meanresult = 0;

	double result;

};

void TTest::Calculate( TTree_symbolic &tree) {
	
	
	for (int i = 0; i < runs; i++)
	{
		optimizer.Init(HML_TestFunction_Griewangk);
		result = optimizer.Start_fast(HML_TestFunction_Griewangk,tree);

		meanresult += fabs(result);

		if (result < eps) reliability++;
	}
	reliability /= double(runs) ;
	meanresult /= double(runs);
}

	