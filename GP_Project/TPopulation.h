#pragma once
#include "TTree.h"
#include "TemplatePopulation.h"
#include "Functions.h"
#include "TFuzzy.h"

class TPopulation_symbolic : public TPopulation<TTree_symbolic> {
public:


	void Calculate_fitness(double **, double *, int, double); //”становить пригодности индивидов регресси¤
	double Get_meansquare();

private:

};

class TPopulation_fuzzy : public TPopulation<TTree_fuzzy> {
public:


	void Calculate_fitness(TFuzzy &); //”становить пригодности индивидов
	vector< vector<int> > Get_best_rules();



private:


};

class TPopulation_DE: public TPopulation<TTree_symbolic> {
public:


	void Calculate_fitness();

private:

};