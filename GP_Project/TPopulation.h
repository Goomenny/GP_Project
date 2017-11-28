#pragma once
#include "TTree.h"
#include "TemplatePopulation.h"

#include "TFuzzy.h"

class TPopulation_symbolic : public TPopulation<TTree_symbolic> {
public:


	void Calculate_fitness(double **, double *, int, double); //Установить пригодности индивидов регрессия

	void Set(double i) { x = i * 3; }
	double Get() { return x; }

private:
	double x = 7;

};

class TPopulation_fuzzy : public TPopulation<TTree_fuzzy> {
public:


	void Calculate_fitness(TFuzzy &); //Установить пригодности индивидов
	vector< vector<int> > Get_best_rules();

	double Get() { return x; }
	void Set(double i) { x = i; }

private:
	double x = 8;

};