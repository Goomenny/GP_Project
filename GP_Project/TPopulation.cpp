#include "TPopulation.h"


void TPopulation_symbolic::Calculate_fitness(double **data, double *y, int size, double max_min) {

	for (int i = 0; i < size_of_population; i++) {
		tree[i].Calculate_fitness(data, y, size, max_min);
	}
}


void TPopulation_fuzzy::Calculate_fitness(TFuzzy& fuzzy) {

	for (int i = 0; i < size_of_population; i++) {
		tree[i].Calculate_fitness(fuzzy);
	}
}

vector< vector<int> > TPopulation_fuzzy::Get_best_rules()
{
	return best_tree.Get_rules();
}
