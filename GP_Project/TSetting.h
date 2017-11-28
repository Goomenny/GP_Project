//---------------------------------------------------------------------------

#ifndef TSettingH
#define TSettingH
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class TSetting
{
private:

protected:
	int num_func; //Функция
	int dimension; //Размерность
	int size_of_population; //Размер популяции
	int max_number_of_populations;  //Макс число поколений
	//Количество операторов каждого вида
	int n_selections;
	int n_crossovers;
	int n_mutations;
	vector<int> type_of_selection;  //Тип селекции      0=prop; 1=rang; 2=tour;
	vector<int> size_of_tour; //Размер турнира для турнирной селекции
	vector<int> type_of_crossover; //Тип скрещивания     0- стандартное 1-одноточечное
	vector<int> type_of_mutation; //Тип мутации


	double probability_of_crossover; //Вероятность скрещивания 0=0.65; 1=0.95; 2=1
	double probability_of_mutation;  //Вероятность мутации

	double accuracy; //Точность поиска

	bool selfconfiguration;

	double selection_probabilities[5];
	double crossover_probabilities[2];
	double mutation_probabilities[3];

	double average_fitness_selection[5];
	double average_fitness_crossover[2];
	double average_fitness_mutation[3];

public:
	void Reset_probabilities();
	TSetting();
	void Recount_probabilities(vector<double>);
	void Calculate_average_fitness(vector<double>);
	void Select_operators();
	//__fastcall ~TSetting();


};
#endif
