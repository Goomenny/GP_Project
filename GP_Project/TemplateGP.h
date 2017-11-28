#pragma once
#include "TSetting.h"


template<class Population>
class TGp : public TSetting
{
protected:
	Population last_population;
	Population new_population;
	Population temp_population;

	int first_solution;
	bool found;
	vector< vector<double> > fitness;
	vector<double> tmp;


	int max_deep, dimension, growth, inheriters;


	Population last_popul;
	int x;
public:

	void Init(bool, int, int, int, int, int, int, int, int, int, int, double, int);  //Инициализация


	double Get_fitness();
	int Get_deep();



	int Get_first_solution();
	vector< vector<double> > Get_stats();

	double Write_x(double u) { return x*u; }
	void Mult(double i) {

		last_popul.Set(i);
		x = last_popul.Get()* i;
	};



};

//---------------------------------------------------------------------------
template<class Population>
void TGp <Population> ::Init(bool selfconfiguration, int num_func, int size_of_population, int max_number_of_populations, int type_of_selection, int size_of_tour, int type_of_crossover, int max_deep, int dimension, int growth, int type_of_mutation, double probability_of_mutation, int inheriters) {
	first_solution = 0;
	found = false;

	this->num_func = num_func;

	//Резервируем память для массивов с примененными операторами
	this->type_of_selection.resize(size_of_population);
	this->size_of_tour.resize(size_of_population);
	this->type_of_crossover.resize(size_of_population);
	this->type_of_mutation.resize(size_of_population);

	if (!selfconfiguration) {
		for (int i = 0; i < size_of_population; i++) {
			this->type_of_selection.push_back(type_of_selection);
			this->size_of_tour.push_back(size_of_tour);
			this->type_of_crossover.push_back(type_of_crossover);
			this->type_of_mutation.push_back(type_of_mutation);
		}
	}
	// Записываем остальные настройки
	this->selfconfiguration = selfconfiguration;
	this->size_of_population = size_of_population;
	this->max_number_of_populations = max_number_of_populations;
	this->dimension = dimension;
	this->probability_of_crossover = probability_of_crossover;
	this->probability_of_mutation = probability_of_mutation;


	this->max_deep = max_deep;
	this->dimension = dimension;
	this->growth = growth;
	this->inheriters = inheriters;
	//Случайно инициализируем первое поколение
	last_population.Init(size_of_population);
	last_population.Init_randomly_tree(max_deep, dimension, growth, inheriters);
	//Инициализируем место для следующиего поколения
	new_population.Init(size_of_population);

}
//---------------------------------------------------------------------------
template<class Population>
double TGp<Population>::Get_fitness() {
	return last_population.Get_best_fitness();
}

//---------------------------------------------------------------------------
template<class Population>
int TGp<Population>::Get_first_solution() {
	if (found) {
		return first_solution;
	}
	else
	{
		return 0;
	}

}
//---------------------------------------------------------------------------
template<class Population>
int TGp<Population>::Get_deep() {
	return last_population.Get_best_tree_deep();
}
//---------------------------------------------------------------------------
template<class Population>
vector< vector<double> > TGp<Population>::Get_stats() {
	return fitness;
}

