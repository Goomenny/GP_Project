#include "TGp.h"
#include <fstream>

//---------------------------------------------------------------------------
double TGp_symbolic::Get_meansquare() {
	return last_population.Get_meansquare();
}
//---------------------------------------------------------------------------
double TGp_symbolic::Get_value(double *var) {
	return last_population.Get_best_value(var);
}
//---------------------------------------------------------------------------
string TGp_symbolic::Get_formula() {
	return last_population.Get_best_formula();
}

//---------------------------------------------------------------------------
int TGp_symbolic::Start_fast(double **data, double *y, int size_of_data, double accuracy, double max_min, bool restart) {

	fitness.clear();

	if (restart) {

		for (int i = 1; i < size_of_population; i++) {
			last_population.ReInit_trees(max_deep, dimension, growth, inheriters);
		}

		if (selfconfiguration) {
			//Сбрасываем вероятности выбора операторов
			Reset_probabilities();
			// Выбираем операторы для первой эволюции
			Select_operators();
		}
	}


	for (int i = 0; i < max_number_of_populations + 1; i++) {

		last_population.Calculate_fitness(data, y, size_of_data, max_min);
		last_population.Find_best();



		tmp.clear();
		double sum = 0;
		for (int ind = 0; ind<size_of_population; ind++) {
			sum += last_population.Get_tree_fitness(ind);
		}
		tmp.push_back(sum / size_of_population);
		tmp.push_back(last_population.Get_best_fitness());
		fitness.push_back(tmp);

		if (last_population.Get_meansquare() <= accuracy&&found == false)
		{
			first_solution = i;
			found = true;
			break;
		}

		if (i<max_number_of_populations) {


			if (selfconfiguration && i != 0)
			{
				//Пересчитываем вероятности операторов

				tmp.clear();
				for (int ind = 0; ind<size_of_population; ind++) {
					tmp.push_back(last_population.Get_tree_fitness(ind));
				}
				Recount_probabilities(tmp);
				Select_operators();
			}

			last_population.Selection(selfconfiguration, type_of_selection, size_of_tour);
			new_population.Evolve(last_population, type_of_crossover);
			new_population.Mutate(type_of_mutation, probability_of_mutation);

			last_population = new_population;


		}
	}

	if (found)
		return 1;
	else
		return 0;


}


//---------------------------------------------------------------------------

vector< vector<int> > TGp_fuzzy::Get_base() {
	return last_population.Get_best_rules();
}

//---------------------------------------------------------------------------

int TGp_fuzzy::Start_fast(TFuzzy& fuzzy, bool restart) {
	fitness.clear();

	if (restart) {


		last_population.ReInit_trees(max_deep, dimension, growth, inheriters);


		if (selfconfiguration) {
			//Сбрасываем вероятности выбора операторов
			Reset_probabilities();
			// Выбираем операторы для первой эволюции
			Select_operators();
		}
	}




	for (int i = 0; i < max_number_of_populations + 1; i++) {

		last_population.Calculate_fitness(fuzzy);
		last_population.Find_best();

		tmp.clear();
		double sum = 0;
		for (int ind = 0; ind<size_of_population; ind++) {
			sum += last_population.Get_tree_fitness(ind);
		}
		tmp.push_back(sum / size_of_population);
		tmp.push_back(last_population.Get_best_fitness());
		fitness.push_back(tmp);

		if (last_population.Get_best_fitness() == 1. / 1.5&&found == false)
		{
			first_solution = i;
			found = true;
			break;
		}

		if (i<max_number_of_populations) {


			if (selfconfiguration && i != 0)
			{
				//Пересчитываем вероятности операторов
				tmp.clear();
				for (int ind = 0; ind<size_of_population; ind++) {
					tmp.push_back(last_population.Get_tree_fitness(ind));
				}
				Recount_probabilities(tmp);
				Select_operators();
			}

			last_population.Selection(selfconfiguration, type_of_selection, size_of_tour);
			new_population.Evolve(last_population, type_of_crossover);
			new_population.Mutate(type_of_mutation, probability_of_mutation);

			last_population = new_population;

		}
	}

	if (found)
		return 1;
	else
		return 0;
}
