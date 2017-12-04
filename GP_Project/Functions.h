#pragma once
#include "HarrixMathLibrary.h"
#include "TTree.h"
#include "DIFFEVO.h"
#include <iostream>
using namespace std;

class TTest
{
public:
	void Calculate( TTree_symbolic &tree);

	double Get_reliability() { return reliability; };
	double Get_meanresult() { return meanresult; };
	double Get_meanx() { return meanx; };

private:
	TDE optimizer;
	int runs = 100;
	double eps = 0.01;

	double reliability = 0;
	double meanresult = 0;
	double meanx = 0;
	double result;
	int D = 3; //Размерность оптимизации
	double bias[3]; //Вектор смещений оптимума

};

void TTest::Calculate( TTree_symbolic &tree) {
	
	bool found = false;
	double *x;
	double tmpx;
	double tmpmeanx=0;
	meanx = 0;
	reliability = 0;
	meanresult = 0;

	for (int i = 0; i < runs; i++)
	{

		for (int d = 0; d < D; d++)
		{
			bias[d] = (rand() % 10001) / 1000. - 5;
		}

		optimizer.Init(HML_TestFunction_ParaboloidOfRevolution,bias);
		result = optimizer.Start_fast(HML_TestFunction_ParaboloidOfRevolution,bias,tree);

		meanresult += fabs(result);

		x = optimizer.Get_bestx();

		tmpmeanx = 0;
		found = true;
		for (int d = 0; d < D; d++)
		{
			tmpx = (x[d] + bias[d])*(x[d] + bias[d]);
			if (tmpx > eps) found= false;
			tmpmeanx +=tmpx;
		}

		meanx += pow(tmpmeanx, 0.5);

		if (found) reliability++;
	}
	reliability /= double(runs);
	meanresult /= double(runs);
	meanx /= double(runs);

}

	