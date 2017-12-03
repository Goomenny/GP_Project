//---------------------------------------------------------------------------

#ifndef TGAPopulationH
#define TGAPopulationH
#include "TGenotype.h"
#include "TFuzzy.h"
//---------------------------------------------------------------------------
class TGAPopulation
{
friend class TGa;
friend class TGASetting;
private:
	TGenotype *genotype; // Массив индивидов
	TGenotype best_genotype; 	// Лучший индивид

	int size_of_population; //Размер популяции
	int *parent[2]; //Пулл родителей
	int *tour; //Массив для номеров индивидов в турнире

	double *proportional_probability; //Вероятность выбора дерева в родители
	double *rank_probability;

public:
	__fastcall TGAPopulation();
	__fastcall ~TGAPopulation();
	__fastcall TGAPopulation(const TGAPopulation &); //Копиконструктор
	TGAPopulation& operator=(const TGAPopulation &); //Копирование популяции

	void Init(int,int,int); //Инициализация популяции (размер)
	void Proportional_selection(); //Пропорциональная селекция
	void Rank_selection();      //Ранговая селекция

	void Calculate_fitness(int *[2],double *,double *,TFuzzy &); //Установить пригодности индивидов
	int Get_parent(int,int);
	void Selection(bool,const vector<int> &,const vector<int> &);

	void Find_best();
	void Evolve(const TGAPopulation &,const vector<int> &);
	void Mutate(const vector<int> &, double);

};
#endif
