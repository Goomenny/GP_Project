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

using namespace std;

// ���������� ������ ������������ �������� ������� arr ������� size
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
// ���������� ������ ������������� �������� ������� arr ������� size
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
int num_func = 0; //�������
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
int size_of_population = 100; //������ ���������
int max_number_of_populations = 100;  //���� ����� ���������
int type_of_selection = 0;  //��� ��������      0=prop; 1=rang; 2=tour;
int size_of_tour = 5; //������ ������� ��� ��������� ��������
int type_of_crossover = 0; //��� �����������     0- ����������� 1-������������
int type_of_mutation = 0;
int max_deep = 3;
int dimension = n_var;
int growth = 0;
double probability_of_mutation = 5 / 100.;  //����������� �������
double accuracy = 0.05; //�������� ������
bool selfconfiguration = false; // ������������� true/false
bool cloning = 1;  //������������




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

	//������� ��������� ����������
	limits.push_back(1);
	limits.push_back(2);
	limits.push_back(M_PI / 6.);
	limits.push_back(2 * M_PI / 3.);
	//�������� ����������
	limits.push_back(1);

	fuzzy.Init(n_var, n_terms, limits);
	fuzzy.Set_truck(truck);



	int inheriters = n_terms[n_var];
	int size_of_population = 50; //������ ���������
	int max_number_of_populations = 100;  //���� ����� ���������
	int type_of_selection = 0;  //��� ��������      0=prop; 1=rang; 2=tour;
	int size_of_tour = 5; //������ ������� ��� ��������� ��������
	int type_of_crossover = 0; //��� �����������     0- ����������� 1-������������
	int type_of_mutation = 0;
	int max_deep = 5;
	int dimension = n_var;
	int growth = 1;
	double probability_of_mutation = 5 / 100.;  //����������� �������


	bool selfconfiguration = true; // ������������� true/false
	bool cloning = 1;  //������������


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
	TDE de;
	de.Init(evaluate);
	de.Start_fast(evaluate);
	regress();
	system("pause");
	return 0;
}