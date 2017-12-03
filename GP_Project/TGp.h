#pragma once
#include "TPopulation.h"
#include "TemplateGP.h"

#include "TFuzzy.h"
class TGp_symbolic : public TGp<TPopulation_symbolic>
{

public:



	int Start_fast(double **, double *, int, double, double, bool);
	string Get_formula();


	double Get_value(double *);
	double Get_meansquare();

};

class TGp_fuzzy : public TGp<TPopulation_fuzzy>
{

public:

	vector< vector<int> > Get_base();
	int Start_fast(TFuzzy &, bool);


};
/*
class TGp_DE: public TGp<TPopulation_DE>
{

public:

	int Start_fast(bool);
	string Get_formula();

	double Get_value(double *);


};
*/