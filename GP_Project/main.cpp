#define _USE_MATH_DEFINES
#include <cstdlib>
#include <ctime>
#include <math.h>

#include "TGp.h"
#include "TGa.h"
#include "TFuzzy.h"
#include "TTruck.h"
#include "Functions.h"
#include "DIFFEVO.h"
#include <iostream>
#include "HarrixMathLibrary.h"
using namespace std;

// Возвращает индекс минимального элемента массива arr размера size
int Min(const double* arr, int size) {
	if (size == 0)
		return -1;

	int min_index = 0;

	for (int i = 1; i < size; i++)
		if (arr[i] < arr[min_index])
			min_index = i;

	return min_index;
}
//---------------------------------------------------------------------------
// Возвращает индекс максимального элемента массива arr размера size
int Max(const double* arr, int size) {
	if (size == 0)
		return -1;

	int max_index = 0;

	for (int i = 1; i < size; i++)
		if (arr[i] > arr[max_index])
			max_index = i;

	return max_index;
}
//---------------------------------------------------------------------------
void regress(){
	srand(time(NULL));
int num_func = 0; //Функция
TGp_symbolic gp;
double **var, *y;

int n_var = 2;

int datasize = 500;
var = new double *[datasize];
y = new double[datasize];

for (int i = 0; i < datasize; i++) {
	var[i] = new double[n_var];
	for (int j = 0; j < n_var; j++) {
		var[i][j] = (rand() % 20001 / 10000. - 1)*M_PI*5.;
	}

	y[i] = Func(var[i], num_func);
}
double max_min = y[Max(y, datasize)] - y[Min(y, datasize)];
int inheriters = 2;
int size_of_population = 100; //Размер популяции
int max_number_of_populations = 100;  //Макс число поколений
int type_of_selection = 0;  //Тип селекции      0=prop; 1=rang; 2=tour;
int size_of_tour = 5; //Размер турнира для турнирной селекции
int type_of_crossover = 0; //Тип скрещивания     0- стандартное 1-одноточечное
int type_of_mutation = 0;
int max_deep = 3;
int dimension = n_var;
int growth = 0;
double probability_of_mutation = 5 / 100.;  //Вероятность мутации
double accuracy = 0.05; //Точность поиска
bool selfconfiguration = false; // Самонастройка true/false
bool cloning = 1;  //Клонирование




gp.Init(selfconfiguration, num_func, size_of_population, max_number_of_populations, type_of_selection, size_of_tour, type_of_crossover, max_deep, dimension, growth, type_of_mutation, probability_of_mutation, inheriters);

gp.Start_fast(var, y, datasize, accuracy, max_min,false);

for (int i = 0; i < gp.Get_stats().size(); i++)
{
	cout << gp.Get_stats()[i][0] << endl;
}

cout<<gp.Get_formula() << endl;
cout << gp.Get_fitness()<<endl;
cout << gp.Get_meansquare() << endl;
cout << gp.Get_deep() << endl;



for (int i = 0; i < datasize; i++) {
	delete[]var[i];
}
delete[]var;
delete[]y;
}


void fuzzy() {
	/*
	TGp gp;
	TGa ga;
	TTruck truck;
	TFuzzy fuzzy;


	int n_var;
	int *n_terms;
	vector<double> limits;
	vector< vector<double> > stats;
	vector< vector <int> > base;


	vector< vector<double> > limit;
	vector< double > tmp;
	vector<double> solution;

	
	n_var = 4;
	n_terms = new int[n_var + 1];

	for (int i = 0; i < n_var + 1; i++) {
		n_terms[i] = 5;
	}

	//Границы изменения переменных
	limits.push_back(1);
	limits.push_back(2);
	limits.push_back(M_PI / 6.);
	limits.push_back(2 * M_PI / 3.);
	//Выходная переменная
	limits.push_back(1);

	fuzzy.Init(n_var, n_terms, limits);
	fuzzy.Set_truck(truck);



	int inheriters = n_terms[n_var];
	int size_of_population = 50; //Размер популяции
	int max_number_of_populations = 100;  //Макс число поколений
	int type_of_selection = 0;  //Тип селекции      0=prop; 1=rang; 2=tour;
	int size_of_tour = 5; //Размер турнира для турнирной селекции
	int type_of_crossover = 0; //Тип скрещивания     0- стандартное 1-одноточечное
	int type_of_mutation = 0;
	int max_deep = 5;
	int dimension = n_var;
	int growth = 1;
	double probability_of_mutation = 5 / 100.;  //Вероятность мутации


	bool selfconfiguration = true; // Самонастройка true/false
	bool cloning = 1;  //Клонирование


	gp.Init(selfconfiguration, 1,size_of_population, max_number_of_populations, type_of_selection, size_of_tour, type_of_crossover, max_deep, dimension, growth, type_of_mutation, probability_of_mutation, inheriters);

	double last_fit = 0;

	do
	{
		last_fit = gp.Get_fitness();
		gp.Start_fast(fuzzy, false);
		vector< vector<double> > tmp = gp.Get_stats();
		stats.insert(stats.end(), tmp.begin(), tmp.end());
		cout << gp.Get_fitness() << endl;
	} while (gp.Get_fitness() != last_fit);



	base = gp.Get_base();

	fuzzy.Set_rules(base);

	double F = 0;
	for (int i = 0; i < 1000; i++) {

		F = fuzzy.Fuzzy_output(truck.var);
		truck.Calculate_O(F);

		cout << truck.Get_O() << '	' << F << endl;
	}
	//truck.Get_X() * 150;
	*/
	
}
int main() {
	srand(time(NULL));

	TTree_symbolic Tree;
	Tree.Init(4, 7, 0, 2);

	TTest test;
	test.Calculate(Tree);
	cout <<Tree.Get_formula() <<endl << test.Get_meanresult() << endl << test.Get_reliability();
	//regress();
	/*
	Tree.Calculate_fitness();
	cout<< Tree.Get_formula()<<endl<<Tree.Get_fitness()<<endl;

	//cout<<optimizer.Start_fast(HML_TestFunction_Griewangk, Tree);

	double var[7]{ 0,1,1,3,4,5,6 };

	cout<<Tree.Get_result(var)<<endl;
	*/
	system("pause");
	return 0;
}