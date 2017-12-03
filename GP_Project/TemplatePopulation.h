#pragma once

#include <vector>

template<class Tree>
class TPopulation
{

protected:
	Tree *tree; // Массив индивидов
	Tree best_tree; 	// Лучший индивид

	int size_of_population; //Размер популяции
	int *parent[2]; //Пулл родителей
	int *tour; //Массив для номеров индивидов в турнире

	double *proportional_probability; //Вероятность выбора дерева в родители
	double *rank_probability;

	int x;


public:
	TPopulation();
	~TPopulation();
	TPopulation(const TPopulation<Tree> &); //Копиконструктор
	TPopulation& operator=(const TPopulation<Tree> &); //Копирование популяции

	void Init(int); //Инициализация популяции (размер)
	void Init_randomly_tree(int, int, int, int); //Случайная инициализация индивидов (размер, макс глубина дерева, кол-во переменных)
	void ReInit_trees(int, int, int, int);
	void Proportional_selection(); //Пропорциональная селекция
	void Rank_selection();      //Ранговая селекция



	int Get_parent(int, int);
	void Selection(bool, const vector<int> &, const vector<int> &);

	void Find_best();
	void Evolve(const TPopulation<Tree> &, const vector<int> &);
	void Mutate(const vector<int> &, double);



	double Get_best_value(double *);
	double Get_meansquare();
	string Get_best_formula();
	double Get_best_fitness();
	double Get_tree_fitness(int) const;
	int Get_best_tree_deep();

	//Временные функции
	int Get_max_deep();




};

template<class Tree>
TPopulation<Tree>::TPopulation() {
	size_of_population = 0;
	tree = 0;
	tour = 0;
	parent[0] = 0;
	parent[1] = 0;
	proportional_probability = 0;
	rank_probability = 0;
}
//---------------------------------------------------------------------------
template<class Tree>
TPopulation<Tree>::~TPopulation() {
	delete[]tree;
	for (int i = 0; i < 2; i++)
		delete[]parent[i];
	delete[]tour;
	delete[]proportional_probability;
	delete[]rank_probability;

}
//---------------------------------------------------------------------------
template<class Tree>
TPopulation<Tree>::TPopulation(const TPopulation<Tree> &other) {

	this->best_tree = other.best_tree; 	// Лучший индивид
	this->size_of_population = other.size_of_population; //Размер популяции

	this->tree = new Tree[size_of_population];
	this->proportional_probability = new double[size_of_population];
	this->rank_probability = new double[size_of_population];
	this->tour = new int[size_of_population];

	for (int i = 0; i < 2; i++) {
		parent[i] = new int[size_of_population];
	}

	for (int i = 0; i < this->size_of_population; i++) {
		this->tree[i] = other.tree[i];
	}

}
//---------------------------------------------------------------------------
template<class Tree>
TPopulation<Tree>& TPopulation<Tree>::operator=(const TPopulation<Tree>  &other) {

	delete[]tree;
	delete[]parent[0];
	delete[]parent[1];
	delete[]tour;
	delete[]proportional_probability;
	delete[]rank_probability;

	this->best_tree = other.best_tree; 	// Лучший индивид
	this->size_of_population = other.size_of_population; //Размер популяции

	this->tree = new Tree[size_of_population];
	this->proportional_probability = new double[size_of_population];
	this->rank_probability = new double[size_of_population];
	this->tour = new int[size_of_population];

	for (int i = 0; i < 2; i++) {
		parent[i] = new int[size_of_population];
	}

	for (int i = 0; i < this->size_of_population; i++) {
		this->tree[i] = other.tree[i];
	}
	return *this;
}
//---------------------------------------------------------------------------
template<class Tree>
void TPopulation<Tree>::Init(int size_of_population) {
	this->size_of_population = size_of_population;

	tree = new Tree[size_of_population];
	proportional_probability = new double[size_of_population];
	rank_probability = new double[size_of_population];
	tour = new int[size_of_population];
	for (int i = 0; i < 2; i++) {
		parent[i] = new int[size_of_population];
	}

}
//---------------------------------------------------------------------------
template<class Tree>
void TPopulation<Tree>::Init_randomly_tree(int max_deep, int dimension, int growth, int inheriters) {

	for (int i = 0; i < size_of_population; i++) {
		tree[i].Init(max_deep, dimension, growth, inheriters);
	}

}

//---------------------------------------------------------------------------

//Пропорциональная селекция
template<class Tree>
void TPopulation<Tree>::Proportional_selection()
{
	double sum = 0; //Сумма всех пригодностей
	for (int i = 0; i < size_of_population; i++) {
		sum += tree[i].Get_fitness();
	}
	for (int i = 0; i < size_of_population; i++) {
		proportional_probability[i] = tree[i].Get_fitness() / sum;
	}

}
//---------------------------------------------------------------------------
//Ранговая селекция
template<class Tree>
void TPopulation<Tree>::Rank_selection()
{   /* Можно ускорить, убрать объявление и удаление)
	(С одинаковым fitness разная вероятность, НУЖНО усреднять) */
	double *fitness_tmp = new double[size_of_population];
	int *num_gen = new int[size_of_population];
	int h = size_of_population / 2;

	for (int i = 0; i < size_of_population; i++)
	{
		fitness_tmp[i] = tree[i].Get_fitness();
		num_gen[i] = i;
	}

	//Сортировка массива методом Шелла
	while (h>0)
	{
		for (int i = 0; i<size_of_population - h; i++)
		{
			int j = i;

			while (j >= 0)
			{
				if (fitness_tmp[j] > fitness_tmp[j + h])
				{
					double tmp;
					int tmp_num;
					tmp = fitness_tmp[j];
					tmp_num = num_gen[j];
					fitness_tmp[j] = fitness_tmp[j + h];
					num_gen[j] = num_gen[j + h];
					fitness_tmp[j + h] = tmp;
					num_gen[j + h] = tmp_num;
					j = j - h;
				}
				else j--;
			}

		}
		h = h / 2;
	}

	for (int i = 0; i < size_of_population; i++) {
		rank_probability[num_gen[i]] = 2.*(i + 1) / (size_of_population*(size_of_population + 1));
	}

	delete[] fitness_tmp;
	delete[] num_gen;

}
//---------------------------------------------------------------------------
template<class Tree>
int TPopulation<Tree>::Get_parent(int type_of_selection, int size_of_tour)
{
	double ran, sum = 0;;
	bool flag = false;
	int num_max = 0;

	if (type_of_selection<2) {
		switch (type_of_selection) {
		case 0:  //Пропорциональная селекция
			ran = rand() % 10000;
			ran /= 10000.;
			for (int i = 0; i < size_of_population; i++)
			{
				sum += proportional_probability[i];
				if (sum>ran)
					return i;
			}
			break;
		case 1: //Ранговая селекция
			ran = rand() % 10000;
			ran /= 10000.;
			for (int i = 0; i < size_of_population; i++)
			{
				sum += rank_probability[i];
				if (sum>ran)
					return i;
			}
			break;
		}

	}
	else {
		//Турнирная селекция /* TODO : Переписать через вектора (для неповторяющегося выбора) */
		for (int i = 0; i < size_of_tour; i++)
		{
			do
			{
				tour[i] = rand() % size_of_population;
				flag = false;
				for (int k = 0; k < i; k++) {
					if (tour[i] == tour[k]) flag = true;
				}
			} while (flag);

		}
		num_max = tour[0];

		for (int i = 1; i < size_of_tour; i++)
			if (tree[tour[i]].Get_fitness()>tree[num_max].Get_fitness())
				num_max = tour[i];

		return num_max;
	}


}
template<class Tree>
void TPopulation<Tree>::Selection(bool selfconfiguration, const vector<int> &type_of_selection, const vector<int> &size_of_tour) {

	if (selfconfiguration) {
		Proportional_selection();
		Rank_selection();
	}
	else {

		if (type_of_selection[0] == 0)
			Proportional_selection();
		else if (type_of_selection[0] == 1)
			Rank_selection();

	}

	for (int i = 0; i < size_of_population; i++) {

		parent[0][i] = Get_parent(type_of_selection[i], size_of_tour[i]);
		do
		{
			parent[1][i] = Get_parent(type_of_selection[i], size_of_tour[i]);
		} while (parent[0][i] == parent[1][i]);

	}



}
//Получение потомка
template<class Tree>
void TPopulation<Tree>::Evolve(const TPopulation<Tree> &last_population, const vector<int> &type_of_crossover) {

	this->tree[0] = last_population.best_tree;
	for (int i = 1; i < size_of_population; i++) {
		//Пытаемся скрестить
		if (!this->tree[i].Crossover(type_of_crossover[i], last_population.tree[last_population.parent[0][i]], last_population.tree[last_population.parent[1][i]]))
			this->tree[i] = last_population.tree[last_population.parent[rand() % 2][i]]; //если неудача до копируем одного из родителей

	}

}
template<class Tree>
void TPopulation<Tree>::Find_best() {
	int n_best = 0;

	for (int i = 1; i < size_of_population; i++)
		if (tree[n_best].Get_fitness()<tree[i].Get_fitness()) n_best = i;
	best_tree = tree[n_best];
}
template<class Tree>
void TPopulation<Tree>::Mutate(const vector<int> &type_of_mutation, double probability_of_mutation) {

	for (int i = 1; i < size_of_population; i++) {
		tree[i].Mutate(type_of_mutation[i], probability_of_mutation);
	}
}
template<class Tree>
void TPopulation<Tree>::ReInit_trees(int max_deep, int dimension, int growth, int inheriters)
{
	for (int i = 1; i < size_of_population; i++) {
		tree[i].Init(max_deep, dimension, growth, inheriters);
	}
}
template<class Tree>
double TPopulation<Tree>::Get_best_value(double * var)
{
	return best_tree.Get_result(var);
}
template<class Tree>
double TPopulation<Tree>::Get_meansquare()
{
	return best_tree.Get_meansquare();
}
template<class Tree>
string TPopulation<Tree>::Get_best_formula()
{
	return best_tree.Get_formula();
}
template<class Tree>
double TPopulation<Tree>::Get_best_fitness()
{
	return best_tree.Get_fitness();
}
template<class Tree>
double TPopulation<Tree>::Get_tree_fitness(int i) const
{
	return tree[i].Get_fitness();
}
template<class Tree>
int TPopulation<Tree>::Get_best_tree_deep()
{
	return best_tree.Get_deep();
}

template<class Tree>
int TPopulation<Tree>::Get_max_deep() {
	int max = tree[0].Get_deep();
	for (int i = 1; i < size_of_population; i++) {
		if (tree[i].Get_deep()>max) max = tree[i].Get_deep();
	}
	return max;
}

